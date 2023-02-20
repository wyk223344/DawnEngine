target("meta_parser")
    set_group("Tools")
    set_kind("binary")
    set_runargs(
        path.join(os.projectdir(), "Source/Engine"),
        path.join(os.projectdir(), "Source/_generated/parser_header.h"), 
        path.join(os.projectdir(), "Source"), 
        "*", 
        "DawnEngine",
        "0")
    add_includedirs("./parser", {public=true})
    add_includedirs("./3rd_party/LLVM/include", {public=true})
    add_includedirs("./3rd_party/mustache", {public=true})
    add_headerfiles("**.h")
    add_linkdirs("./3rd_party/LLVM/lib/x64", {public = true})
    add_links("libclang", {public=true})
    add_files("**.cpp")
    --add_configfiles("precompile.json.in")
    
    after_build(function(target)
        os.cp(path.join(target:scriptdir(), "3rd_party/LLVM/bin/x64/libclang.dll"), target:targetdir())

        --os.exec("xmake run meta_parser")
    end)