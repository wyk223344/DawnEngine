target("Editor")
    set_kind("binary")
    add_deps("Engine")
    add_includedirs("../", {public=true})
    add_headerfiles("**.h")
    add_files("**.cpp")