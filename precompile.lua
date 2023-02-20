--includes("Source/Tools/xmake.lua")

function main(script)

    local projectFileName = path.join(os.projectdir(), "Source/Engine")
    local includeFileNameToGenerate = path.join(os.projectdir(), "Source/_generated/parser_header.h")
    local projectBaseDirectory = path.join(os.projectdir(), "Source")

    os.exec(string.format("xmake run meta_parser %s %s %s %s %s 0", projectFileName, includeFileNameToGenerate, projectBaseDirectory, "*", "DawnEngine"))
end