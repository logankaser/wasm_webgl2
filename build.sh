machine=default

docker-machine ssh $machine sudo rm -rf /home/docker/build
docker-machine ssh $machine mkdir /home/docker/build

echo "Sending build data to server.."
mkdir -p obj
scp -i ~/.docker/machine/machines/$machine/id_rsa -pqr . docker@$(docker-machine ip $machine):/home/docker/build
echo "------------------------------\n"

docker start wasm_build_server > /dev/null
docker exec -ti wasm_build_server bash -c ". /root/emsdk/emsdk_env.sh > /dev/null; make -C /root/build"
docker stop wasm_build_server > /dev/null

echo "\n------------------------------"
echo "Fetching result from server..."
scp -i ~/.docker/machine/machines/$machine/id_rsa -pqr docker@$(docker-machine ip $machine):/home/docker/build/\* .
echo "Done."