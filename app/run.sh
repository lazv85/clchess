#!/bin/sh
docker run -it --rm --name=example \
	--mount type=bind,source=${PWD},target=/src \
    chess:latest \
	bash