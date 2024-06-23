# Docker

> - <https://www.docker.com/>
> - [Docker Roadmap](https://roadmap.sh/docker)

## Zero Downtime

- <https://medium.com/@limone.eth/deploy-docker-containers-with-zero-downtime-ed06b0a0966d>
- <https://github.com/limone-eth/docker-zero-downtime-deployments>

## Docker Build

### Building images

#### Multi-stage builds

- <https://docs.docker.com/build/building/multi-stage/#use-multi-stage-builds>

## Docker Networks

在 Docker Compose 文件中，如果没有显式指定网络名称，Docker Compose 会自动创建一个默认网络。
这个默认网络的名称格式通常为：`<项目名>_default`

- 其中 `<项目名>` 默认为 Compose 文件所在目录的名称
- 或者可以指定项目名（`-p`）

## Docker Registry

```sh
docker tag IMAGE_HASH REGISTRY.domain/IMAGE_NAME:TAG
docker push REGISTRY.domain/IMAGE_NAME:TAG
```
