# mem_dlfunc
绕过Android native dlopen namespace限制，让app在native层可以直接dlopen系统so（例如libart.so）并获取其方法地址。 支持动态符号表导出的函数/符号表非导出的函数。更新自“https://github.com/avs333/Nougat_dlfunctions”

Bypass the Android native dlopen namespace restrictions, allowing an app to directly dlopen system shared libraries (e.g., libart.so) and retrieve their method addresses in the native layer. Supports functions exported in the dynamic symbol table as well as those not exported in the symbol table. Updated from "https://github.com/avs333/Nougat_dlfunctions".
