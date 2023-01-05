module_root = path.absolute("xmake")
import("find_sdk", {rootdir = module_root})

find_sdk.tool_from_github("dxc", "dxc-windows-x64.zip")