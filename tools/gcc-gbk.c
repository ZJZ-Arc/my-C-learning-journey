/*
 * gcc-gbk.c —— gcc 的转发器（wrapper）
 *
 * 它做四件事：
 *   1. 把自己 PATH 最前面插上 MSYS2 的 bin 目录 —— gcc 的子程序 cc1.exe / as.exe
 *      需要那里的 DLL（libgmp、libmpfr、libisl…）。不插的话，在 PATH 干净的
 *      环境里（比如没重启的 VS Code）gcc 会**静默退出 1、一个字都不报**。
 *   2. 强制把 TEMP/TMP/TMPDIR 指向纯 ASCII 目录并补上 -static ——
 *      汇编器 as.exe 在中文路径下创建 .o 会失败
 *      （Fatal error: can't create ...\ccXXXX.o）；-static 让 exe 不依赖 MSYS2 的 DLL。
 *   3. 强制补上编码参数：-finput-charset=UTF-8 -fexec-charset=GBK，
 *      让 exe 里存 GBK 字节，匹配中文 Windows 的 936 控制台。
 *   4. 【中文路径兜底】如果 -o 指定的输出路径含非 ASCII 字符（例如
 *      D:\runbank\test\第二周\temperature.exe），就先让 gcc 生成到一个 ASCII
 *      临时目录，成功后由本程序搬回原位置。
 *      原因：gcc 启动 ld.exe 时会把参数转成 ANSI 编码，中文变成 ????，报
 *      "ld.exe: cannot open output file ...: No such file or directory"。
 *      注意：只识别 "-o 路径" 这种分开写的形式（VS Code 的任务、cpptools、
 *      Code Runner 都是这么调的）。
 *
 * 为什么要它：VS Code 里好几个"运行/编译"按钮（cpptools、cpp-devtools 的 ▶）
 * 用自己的命令直接调 gcc，不读 tasks.json，于是编出 UTF-8 的 exe，双击乱码。
 * 把 c_cpp_properties.json 的 compilerPath 指向本程序，这些按钮就自动正确了。
 *
 * 编译：gcc -O2 -static -o gcc-gbk.exe gcc-gbk.c -lshell32
 */

#include <windows.h>
#include <shellapi.h>
#include <stdio.h>
#include <wchar.h>

#define MSYS_BIN   L"C:\\msys64\\ucrt64\\bin"
#define MSYS_TMP   L"C:\\msys64\\tmp"
#define REAL_GCC   L"C:\\msys64\\ucrt64\\bin\\gcc.exe"
#define EXTRA_ARGS L" -finput-charset=UTF-8 -fexec-charset=GBK -static"

#define MAXCMD 32767

/* 按 Windows 命令行规则给参数加引号（处理空格、引号、结尾反斜杠） */
static void append_quoted(wchar_t *dst, size_t cap, const wchar_t *arg)
{
    size_t len = wcslen(dst);
    size_t alen = wcslen(arg);

    if (len + alen + 10 >= cap) return;     /* 放不下就跳过，避免越界 */

    dst[len++] = L' ';                      /* 参数之间必须有空格分隔 */
    dst[len] = L'\0';

    if (alen > 0 && wcspbrk(arg, L" \t\"") == NULL) {
        wcscat(dst, arg);
        return;
    }

    dst[len++] = L'"';
    size_t backslashes = 0;
    for (size_t i = 0; i < alen; i++) {
        wchar_t ch = arg[i];
        if (ch == L'\\') {
            backslashes++;
            dst[len++] = ch;
        } else if (ch == L'"') {
            for (size_t k = 0; k < backslashes + 1; k++) dst[len++] = L'\\';
            backslashes = 0;
            dst[len++] = L'"';
        } else {
            backslashes = 0;
            dst[len++] = ch;
        }
    }
    for (size_t k = 0; k < backslashes; k++) dst[len++] = L'\\';   /* 结尾反斜杠要加倍 */
    dst[len++] = L'"';
    dst[len] = L'\0';
}

static int is_ascii(const wchar_t *s)
{
    for (; *s; s++) if (*s > 127) return 0;
    return 1;
}

int main(void)
{
    /* ---- 1) PATH 兜底 ---- */
    static wchar_t oldpath[MAXCMD];
    DWORD n = GetEnvironmentVariableW(L"PATH", oldpath, MAXCMD);

    static wchar_t newpath[MAXCMD];
    _snwprintf_s(newpath, MAXCMD, _TRUNCATE, L"%s;%s",
                 MSYS_BIN, (n > 0 && n < MAXCMD) ? oldpath : L"");
    SetEnvironmentVariableW(L"PATH", newpath);

    /* ---- 2) TEMP 兜底（不存在就创建；已存在时 CreateDirectory 会失败，忽略） ---- */
    CreateDirectoryW(MSYS_TMP, NULL);
    SetEnvironmentVariableW(L"TEMP", MSYS_TMP);
    SetEnvironmentVariableW(L"TMP", MSYS_TMP);
    SetEnvironmentVariableW(L"TMPDIR", MSYS_TMP);

    /* ---- 解析原始参数（Unicode 版，中文不会坏） ---- */
    int argc = 0;
    LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv || argc < 1) return 1;

    /* ---- 3) 找出 -o 的输出路径；含中文就改用 ASCII 临时输出 ---- */
    static wchar_t outReal[MAXCMD];     /* 用户要求的输出路径（已转绝对路径） */
    static wchar_t outTemp[MAXCMD];     /* 需要转手时的临时输出 */
    outReal[0] = outTemp[0] = L'\0';

    for (int i = 1; i + 1 < argc; i++) {
        if (wcscmp(argv[i], L"-o") == 0) {
            DWORD m = GetFullPathNameW(argv[i + 1], MAXCMD, outReal, NULL);
            if (m == 0 || m >= MAXCMD) outReal[0] = L'\0';
        }
    }

    if (outReal[0] && !is_ascii(outReal)) {
        const wchar_t *dot = wcsrchr(outReal, L'.');
        const wchar_t *ext = (dot && !wcschr(dot, L'\\')) ? dot : L".out";
        _snwprintf_s(outTemp, MAXCMD, _TRUNCATE,
                     L"%s\\gcc-gbk-%lu%s", MSYS_TMP, GetCurrentProcessId(), ext);
        DeleteFileW(outTemp);
    }

    /* ---- 拼出真正要执行的 gcc 命令行 ---- */
    static wchar_t full[MAXCMD];
    _snwprintf_s(full, MAXCMD, _TRUNCATE, L"\"" REAL_GCC L"\"" EXTRA_ARGS);

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-o") == 0 && i + 1 < argc && outTemp[0]) {
            append_quoted(full, MAXCMD, L"-o");
            append_quoted(full, MAXCMD, outTemp);       /* 先写到 ASCII 临时路径 */
            i++;                                        /* 原输出路径已被替换 */
            continue;
        }
        append_quoted(full, MAXCMD, argv[i]);
    }

    /* ---- 执行 gcc ---- */
    STARTUPINFOW si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    if (!CreateProcessW(NULL, full, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        fwprintf(stderr, L"gcc-gbk: 无法启动 gcc（错误码 %lu）\n", GetLastError());
        return 1;
    }
    WaitForSingleObject(pi.hProcess, INFINITE);
    DWORD code = 0;
    GetExitCodeProcess(pi.hProcess, &code);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    /* ---- 4) 编译成功就把产物搬回用户要的位置（MoveFileExW 是 Unicode 的） ---- */
    if (outTemp[0]) {
        if (code == 0) {
            if (!MoveFileExW(outTemp, outReal,
                             MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED)) {
                fwprintf(stderr,
                         L"gcc-gbk: 编译成功，但无法把输出移动到 %ls（错误码 %lu）\n",
                         outReal, GetLastError());
                DeleteFileW(outTemp);
                return 1;
            }
        } else {
            DeleteFileW(outTemp);       /* 编译失败，别留垃圾 */
        }
    }

    return (int)code;
}
