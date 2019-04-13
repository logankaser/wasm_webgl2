machine=default

docker-machine ssh $machine sudo rm -rf /home/docker/build
docker-machine ssh $machine mkdir /home/docker/build

scp -i ~/.docker/machine/machines/$machine/id_rsa -p -r . docker@$(docker-machine ip $machine):/home/docker/build

docker start wasm_build_server
docker exec -ti wasm_build_server bash -c ". /root/emsdk/emsdk_env.sh; make -C /root/build"
docker stop wasm_build_server

scp -i ~/.docker/machine/machines/$machine/id_rsa -p -r docker@$(docker-machine ip $machine):/home/docker/build/\* .
