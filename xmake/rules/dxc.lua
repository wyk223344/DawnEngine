rule("utils.dxc")
    set_extensions(".hlsl")
    on_load(function (target)
        local headerdir = path.join(target:autogendir(), "rules", "utils", "dxc")
        if not os.isdir(headerdir) then
            os.mkdir(headerdir)
        end
        target:add("includedirs", headerdir)
    end)
    before_buildcmd_file(function (target, batchcmds, sourcefile_hlsl, opt)
        --import("find_sdk")
        import("find_sdk")
        dxc = find_sdk.find_program("dxc")

        -- get target profile
        target_profile = sourcefile_hlsl:match("^.+%.(.+)%.")
        hlsl_basename = path.filename(sourcefile_hlsl):match("(.+)%..+%..+")

        -- hlsl to dxil
        local dxil_outputdir = path.join(os.projectdir(), "Shaders", "generated")
        local dxilfilepath = path.join(dxil_outputdir, hlsl_basename .. ".h")

        if not opt.quiet then
            batchcmds:show_progress(opt.progress, "${color.build.object}[%s]: compiling.dxil %s -> %s", 
                target:name(), sourcefile_hlsl, hlsl_basename .. ".h")
        end

        batchcmds:mkdir(dxil_outputdir)
        batchcmds:vrunv(dxc.vexec, 
            {"-Wno-ignored-attributes", 
            "-all_resources_bound", 
            "-Fh ", dxilfilepath, 
            "-Vn ", ("g_Shader"..hlsl_basename),
            "-T ", target_profile,
            path.join(os.projectdir(), sourcefile_hlsl)})
            
        -- add deps
        batchcmds:add_depfiles(sourcefile_hlsl)
        batchcmds:set_depmtime(os.mtime(dxilfilepath))
        batchcmds:set_depcache(target:dependfile(dxilfilepath))
    end)

