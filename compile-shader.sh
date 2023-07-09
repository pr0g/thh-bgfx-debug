./third-party/build/bin/shaderc \
-f src/shader/instance_uv/vs_instance_uv.sc \
-o src/shader/instance_uv/vs_instance_uv.bin \
--platform osx --type vertex --verbose -i ./ -p metal

./third-party/build/bin/shaderc \
-f src/shader/instance_uv/fs_instance_uv.sc \
-o src/shader/instance_uv/fs_instance_uv.bin \
--platform osx --type fragment --verbose -i ./ -p metal
