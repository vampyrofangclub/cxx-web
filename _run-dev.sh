docker rm -f docker-project || true && \
docker build -f _docker/Dockerfile -t docker-project-image _docker && \
docker run --name docker-project -it -v $(pwd):$(pwd) -p 9229:9229 -p 3000:3000 -w $(pwd) docker-project-image /bin/bash