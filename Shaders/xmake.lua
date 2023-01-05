
target("ShaderCompiler")
    set_kind("static")
    add_rules("utils.dxc")
    add_files("**.hlsl")
    add_headerfiles("**.hlsl")
    add_headerfiles("**.hlsli")