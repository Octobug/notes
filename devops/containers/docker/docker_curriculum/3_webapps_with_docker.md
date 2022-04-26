# Webapps with Docker

> <https://docker-curriculum.com/#webapps-with-docker>

- [Webapps with Docker](#webapps-with-docker)
  - [Static Sites](#static-sites)
  - [Docker Images](#docker-images)
  - [Our First Image](#our-first-image)
  - [Dockerfile](#dockerfile)
  - [Docker on AWS](#docker-on-aws)
    - [Docker push](#docker-push)

## Static Sites

```sh
# --rm flag removes the container when it exits
# -it specifies an interactive terminal
docker run --rm -it prakhar1989/static-site
```

```sh
# -d detechs terminal
# -P publishes all exposed ports to random ports
# --name gives the container a name
docker run -d -P --name static-site prakhar1989/static-site
```

```sh
# see container's ports
docker port static-site
```

You can also specify a custom port to which the client will forward connections
to the container.

```sh
docker run -d -p 8888:80 --name static-site prakhar1989/static-site
```

```sh
docker stop static-site
```

## Docker Images

```sh
$ docker images
REPOSITORY          TAG     IMAGE ID        CREATED         VIRTUAL SIZE
prakhar1989/catnip  latest  c7ffb5626a50    2 hours ago     697.9 MB
```

The `TAG` refers to a particular snapshot of the image and the `IMAGE ID` is
the corresponding unique identifier for that image.

For simplicity, you can think of an image akin to a git repository - images can
be committed with changes and have multiple versions. If you don't provide a
specific version number, the client defaults to latest. For example, you can
pull a specific version of `ubuntu` image

```sh
docker pull ubuntu:18.04
docker search
```

An important distinction to be aware of when it comes to images is the
difference between **base** and **child** images.

- Base images are images that have no parent image, usually images with an OS
  like ubuntu, busybox or debian.
- Child images are images that build on base images and add additional
  functionality.

Then there are official and user images, which can be both base and child images.

- Official images are images that are officially maintained and supported by
  the folks at Docker. These are typically one word long. In the list of images
  above, the `python`, `ubuntu`, `busybox` and `hello-world` images are
  official images.
- User images are images created and shared by users like you and me. They
  build on base images and add additional functionality. Typically, these are
  formatted as `user/image-name`.

## Our First Image

```sh
git clone https://github.com/prakhar1989/docker-curriculum.git
cd docker-curriculum/flask-app
```

## Dockerfile

A Dockerfile is a simple text file that contains a list of commands that the
Docker client calls while creating an image.

To start, create a new blank file in our favorite text-editor and save it in
the same folder as the flask app by the name of `Dockerfile`:

```docker
# STEP 1: choose a base image
FROM python:3.8

# STEP 2: copying files & installing dependencies
# set a directory for the app
WORKDIR /usr/src/app

# copy all the files to the container
COPY . .

# install dependencies
RUN pip install --no-cache-dir -r requirements.txt

# STEP 3: expose port for communication
# tell the port number the container should expose
EXPOSE 5000

# STEP 4: start the app
# run the command
CMD ["python", "./app.py"]
```

The primary purpose of `CMD` is to tell the container which command it should
run when it is started.

The `docker build` command does the heavy-lifting of creating a Docker image
from a `Dockerfile`.

The username should be the same one you created when you registered on Docker
hub. The `docker build` command is quite simple - it takes an optional tag name
with `-t` and a location of the directory containing the `Dockerfile`.

```sh
$ docker build -t yourusername/catnip .
Sending build context to Docker daemon 8.704 kB
Step 1 : FROM python:3.8
# Executing 3 build triggers...
Step 1 : COPY requirements.txt /usr/src/app/
 ---> Using cache
Step 1 : RUN pip install --no-cache-dir -r requirements.txt
 ---> Using cache
Step 1 : COPY . /usr/src/app
 ---> 1d61f639ef9e
Removing intermediate container 4de6ddf5528c
Step 2 : EXPOSE 5000
 ---> Running in 12cfcf6d67ee
 ---> f423c2f179d1
Removing intermediate container 12cfcf6d67ee
Step 3 : CMD python ./app.py
 ---> Running in f01401a5ace9
 ---> 13e87ed1fbc2
Removing intermediate container f01401a5ace9
Successfully built 13e87ed1fbc2
```

```sh
$ docker run -p 8888:5000 yourusername/catnip
 * Running on http://0.0.0.0:5000/ (Press CTRL+C to quit)
```

## Docker on AWS

### Docker push

```sh
$ docker login
Login in with your Docker ID to push and pull images from Docker Hub. If you do
    not have a Docker ID, head over to https://hub.docker.com to create one.
Username: yourusername
Password:
WARNING! Your password will be stored unencrypted in /Users/yourusername/.docker/config.json
Configure a credential helper to remove this warning. See
https://docs.docker.com/engine/reference/commandline/login/credential-store

Login Succeeded
```

To publish, just type the below command remembering to replace the name of the
image tag above with yours. It is important to have the format of
`yourusername/image_name` so that the client knows where to publish.

```sh
docker push yourusername/catnip

# run a container from image on a remote registry
docker run -p 8888:5000 yourusername/catnip
```
