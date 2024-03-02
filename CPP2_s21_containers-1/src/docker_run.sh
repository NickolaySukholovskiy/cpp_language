#!/bin/bash
docker rmi -f s21ubuntu_gtest
docker build . -t s21ubuntu_gtest
docker run -it s21ubuntu_gtest 