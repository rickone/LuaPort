function shell(szCmd)
	--print("shell: "..szCmd);
	local pipe = io.popen(szCmd, "r");
	local out = pipe:read("*a");
	pipe:close();
	return unpack(line_in_table(out));
end

function execute(szCmd)
	--print("execute: "..szCmd);
	return os.execute(szCmd);
end

function each_line(szText)
	return string.gmatch(szText, "(.-)\n");
end

function line_in_table(szText)
	local tb = {};
	for line in each_line(szText) do
		table.insert(tb, line);
	end
	return tb;
end

function is_file_exists(szFile)
	local f = io.open(szFile, "rb");
	if f then
		f:close();
		return true;
	end
	return false;
end

function get_obj_file(szSrcFile, szObjDir)
	local szObjFile = string.gsub(szSrcFile, "(.+)%..+", "%1.o");
	return szObjDir.."/"..szObjFile;
end

function is_newer(szSrcFile, szObjFile)
	if not is_file_exists(szObjFile) then
		return true;
	end
	local t1, t2 = shell("stat --format=%Y "..szSrcFile.." "..szObjFile);
	return tonumber(t1) > tonumber(t2);
end

Product = "lua";
Platform = shell("uname");
Include = "";
LibDir = "../../Library/"..Platform.."/"..Product;
ObjDir = "../../Build/"..Platform.."/"..Product;
Src = {shell("ls *.c")};
Compiler = "gcc -m32 -c -g -D_DEBUG -o ";
Linker = "ar cr ";
Target = LibDir.."/"..Product.."D.a";

execute("mkdir -p "..LibDir);
execute("mkdir -p "..ObjDir);
local szTotalObj = "";
for _, szSrcFile in ipairs(Src) do
	--print("src:<"..szSrcFile..">");
	local szObjFile = get_obj_file(szSrcFile, ObjDir);
	if is_newer(szSrcFile, szObjFile) then
		print(">Compile "..szSrcFile.." ...");
		local code = execute(Compiler..szObjFile.." "..szSrcFile);
		if code ~= 0 then
			print(">>build failed!");
			os.exit(code);
		end
	end
	szTotalObj = szTotalObj.." "..szObjFile;
end
local code = execute(Linker..Target..szTotalObj);
print(">>build "..(code == 0 and "succeed." or "failed!"));
os.exit(code);
