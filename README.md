# tcp-client-server
communication between Client(C++) Server(py3) on Docker 
first commit
# TCP/IP client-server communicating over socket and running over docker containers


## Quick Overview

First we have to build our containers using docker compose
```sh
docker-compose up build
```
Then we run our 2 containers
```sh
docker-compose up -d
```
We use the `-d` to run in detached mode

## Check the logs
Once our containers are running, we can check what is actually happening on the client and the server by checking the docker logs:

```sh
docker ps
```

```sh
docker logs --follow <CONTAINER_ID>
```
