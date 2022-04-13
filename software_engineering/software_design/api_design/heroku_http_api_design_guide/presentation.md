# 学习《HTTP API 设计指南》

> 《HTTP API 设计指南》: [ZhangBohan/http-api-design-ZH_CN](https://github.com/ZhangBohan/http-api-design-ZH_CN)

## 前言

这篇指南介绍描述了 `HTTP`+`JSON` API 的一种设计模式，最初摘录整理自 Heroku 平台的 API
设计指引 [Heroku 平台 API 指引](https://devcenter.heroku.com/articles/platform-api-reference)。

这篇指南除了详细介绍现有的 API 外，Heroku 将来新加入的内部 API 也会符合这种设计模式，
我们希望非 Heroku 员工的 API 设计者也能感兴趣。

我们的目标是保持一致性，专注业务逻辑同时避免过度设计。我们一直试图找出一种**良好的**、
**一致的**、**有据可查**的 API 设计方法，而并不是所谓的"终极/理想模式"。

我们假设你熟悉基本的 `HTTP`+`JSON` API 设计方法，所以本篇指南并不包含所有的 API 设计基础。

- [学习《HTTP API 设计指南》](#学习http-api-设计指南)
  - [前言](#前言)
  - [基础](#基础)
    - [隔离关注点](#隔离关注点)
    - [要求使用安全连接 (Secure Connections)](#要求使用安全连接-secure-connections)
    - [要求在头信息 Accept 中提供版本号](#要求在头信息-accept-中提供版本号)
    - [支持 Etags 缓存](#支持-etags-缓存)
    - [为内省提供 Request-Id](#为内省提供-request-id)
    - [通过请求中的范围 (Range) 拆分大的响应](#通过请求中的范围-range-拆分大的响应)
  - [请求 (Requests)](#请求-requests)
    - [请求体使用 JSON 格式](#请求体使用-json-格式)
    - [资源名称 (Resource names)](#资源名称-resource-names)
    - [行为 (Actions)](#行为-actions)
    - [使用统一的资源路径格式](#使用统一的资源路径格式)
      - [路径与属性名使用小写](#路径与属性名使用小写)
      - [支持无 ID 间接引用](#支持无-id-间接引用)
      - [最小化路径嵌套](#最小化路径嵌套)
  - [响应 (Responses)](#响应-responses)
    - [返回适当的状态码](#返回适当的状态码)
    - [提供全部可用的资源](#提供全部可用的资源)
    - [为资源提供 (UU)ID](#为资源提供-uuid)
    - [提供标准的时间戳](#提供标准的时间戳)
    - [提供标准的响应数据类型](#提供标准的响应数据类型)
      - [String](#string)
      - [Boolean](#boolean)
      - [Number](#number)
      - [Array](#array)
      - [Object](#object)
    - [使用 ISO8601 格式的 UTC (Coordinated Universal Time) 时间](#使用-iso8601-格式的-utc-coordinated-universal-time-时间)
    - [嵌套外键关系](#嵌套外键关系)
    - [生成结构化的错误](#生成结构化的错误)
    - [显示频率限制状态](#显示频率限制状态)
    - [保持响应 JSON 最小化](#保持响应-json-最小化)
  - [工件 (Artifacts)](#工件-artifacts)
    - [提供机器可读的 JSON Schema](#提供机器可读的-json-schema)
    - [提供人类可读的文档](#提供人类可读的文档)
    - [提供可执行的例子](#提供可执行的例子)
    - [描述稳定性](#描述稳定性)
  - [参考资料](#参考资料)
  - [扩展阅读](#扩展阅读)

## 基础

基础部分概述了指南其余部分所依据的设计原则。

### 隔离关注点

设计时通过将请求和响应之间的不同部分隔离来让事情变得简单。
保持简单的规则让我们能更关注在一些更大的更困难的问题上。

请求和响应用于处理特定的资源或集合。使用路径 (path) 来表明身份，body 来传输内容 (content)
还有头信息 (headers) 来传递元数据（metadata）。查询参数 (URL query params)
同样可以用来传递头信息的内容，但头信息是首选，因为他们更灵活、更能传达不同的信息。

<details>
  <summary>Heroku API Request/Response Headers Sample</summary>

---

Request:

```http2
:authority: api.heroku.com
:method: GET
:path: /apps
:scheme: https
accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,
  image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9
accept-encoding: gzip, deflate, br
accept-language: zh,zh-CN;q=0.9
cache-control: max-age=0
cookie: xxx
sec-ch-ua: " Not A;Brand";v="99", "Chromium";v="100", "Google Chrome";v="100"
sec-ch-ua-mobile: ?0
sec-ch-ua-platform: "macOS"
sec-fetch-dest: document
sec-fetch-mode: navigate
sec-fetch-site: none
sec-fetch-user: ?1
upgrade-insecure-requests: 1
user-agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7)
  AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.75 Safari/537.36
```

Response:

```http2
content-length: 159
content-type: application/json; charset=utf-8
date: Tue, 12 Apr 2022 09:20:57 GMT
request-id: 5407b595-9ea5-481c-b3da-29e4c526ea3e,
  ae601b96-d4f5-90db-3f51-ef462c71e80a,a4132c45-3694-ebf7-7f04-d313bb6f8eee
traceparent: 00-5d171ca4bd996ec5bb6c84ac9602864b-96e13818744d65b3-01
via: 1.1 spaces-router (1ee3716bf5eb), 2.0 spaces-router (1ee3716bf5eb)
```

</details>

### 要求使用安全连接 (Secure Connections)

所有的 API 访问都要求使用 TLS 安全连接。没有必要去区分或解释什么情况下需要 TLS
什么情况不需要，直接强制任何访问都要通过 TLS。

理想状态下，通过拒绝所有非 TLS 请求，不响应 HTTP 或 80 端口的请求以避免任何不安全的数据交换。
如果现实情况中无法这样做，可以返回 `403 Forbidden` 响应。

把非 TLS 的请求重定向 (Redirect) 至 TLS 连接是不明智的，
这种含混/不好的客户端行为不会带来明显好处。依赖于重定向的客户端访问不仅会导致双倍的服务器负载，
还会使 TLS 加密失去意义，因为在首次非 TLS 调用时，敏感信息就已经暴露出去了。

### 要求在头信息 Accept 中提供版本号

制定版本并在版本之间平缓过渡对于设计和维护一套 API 是个巨大的挑战。所以，
最好在设计之初就使用一些方法来预防可能会遇到的问题。

为了避免 API 的变动导致用户使用中产生意外结果或调用失败，最好强制要求所有访问都需要指定版本号。
请避免提供默认版本号，一旦提供，日后想要修改它会相当困难。

最适合放置版本号的位置是头信息 (HTTP Headers)，在 `Accept` 段中使用自定义类型
(content type) 与其他元数据 (metadata) 一起提交。例如:

```http
Accept: application/vnd.heroku+json; version=3
```

<details>
  <summary>How does Heroku require API version in HTTP Accept Header?</summary>

---

```sh
$ curl -nX GET https://api.heroku.com/apps/01234567-89ab-cdef-0123-456789abcdef

{
  "id":"missing_version",
  "error":"Please specify a version along with Heroku's API MIME type.
    For example, `Accept: application/vnd.heroku+json; version=3`.\n"
}

$ curl -nX GET https://api.heroku.com/apps/01234567-89ab-cdef-0123-456789abcdef \
-H "Accept: application/vnd.heroku+json; version=3"

{
  "resource": "app",
  "id": "not_found",
  "message": "Couldn't find that app."
}
```

</details>

<details>
  <summary>Why have version in headers and not URLs?</summary>

---

> - [Repo Issue](https://github.com/interagent/http-api-design/issues/47)
> - [mark nottingham - Web API Versioning Smackdown](https://www.mnot.net/blog/2011/10/25/web_api_versioning_smackdown)

URL `http://api.example.com/v1/things/foo`, `http://api.example.com/v2/things/foo`

vs.

HTTP Header `Accept: version=2`, `Accept: version=3`

</details>

### 支持 Etags 缓存

在所有响应中包含 `ETag` 头信息，用来标识资源的版本。这让用户对资源进行缓存处理成为可能，
在后续的访问请求中把 `If-None-Match` 头信息设置为之前得到的 `ETag` 值，
就可以侦测到已缓存的资源是否需要更新。

<details>
  <summary>ETag?</summary>

---

ETag: Entity Tag

</details>

### 为内省提供 Request-Id

为每一个请求响应包含一个 `Request-Id` 头，并使用 UUID 作为该值。通过在客户端、
服务器或任何支持服务上记录该值，它能为我们提供一种机制来跟踪、诊断和调试请求。

### 通过请求中的范围 (Range) 拆分大的响应

一个大的响应应该通过多个请求使用 `Range` 头信息来拆分，并指出如何获取。
详细的请求和响应的头信息 (header)，状态码 (status code)，范围 (limit)，排序 (ordering)
和迭代 (iteration) 等，请参考 [Heroku Platform API discussion of Ranges](https://devcenter.heroku.com/articles/platform-api-reference#ranges).

<details>
  <summary>Further explanation of the Range header for pagination</summary>

---

> [Repo Issue](https://github.com/interagent/http-api-design/issues/36)

We chose `..` as a delimiter. Byte ranges use `-`
(`Content-Range: <unit> <range-start>-<range-end>/<size>`), but we didn't feel
that was unique enough as uuids at least also contain this value, so `..` seems
less ambiguous and is an established convention elsewhere for use as a
delimiter. You can supply one or both ends, so if we were ranging over the
alphabet, you can do things like:

- `a..z` to get everything
- `a..` to get the default size worth of results greater than or equal to `a`
- `..z` to get the default size worth of results less than or equal to `z`
- `]a..` results greater than `a` (not greater than or equal as above)
- `..z[` results less than z (not less than or equal as above)

</details>

## 请求 (Requests)

请求部分概述了 API 请求的模式。

### 请求体使用 JSON 格式

在 `PUT`/`PATCH`/`POST` 请求体 (request bodies) 中使用 JSON 格式数据，
而非 form 表单形式编码的数据。这与我们使用 JSON 格式返回响应体相对应，例如:

```sh
$ curl -X POST https://service.com/apps \
    -H "Content-Type: application/json" \
    -d '{"name": "demoapp"}'

{
  "id": "01234567-89ab-cdef-0123-456789abcdef",
  "name": "demoapp",
  "owner": {
    "email": "username@example.com",
    "id": "01234567-89ab-cdef-0123-456789abcdef"
  },
  ...
}
```

### 资源名称 (Resource names)

使用复数形式命名资源，除非这个资源在系统中是单例的
(例如，一个系统的整体状态可能是 `/status`)。 这种方式使得对资源的引用方式保持统一性。

### 行为 (Actions)

好的端点不应该指定资源的特殊行为，在某些情况下，为资源指定行为却是必要的。
这时应该在行为前加上一个清晰的 `actions` 前缀:

```path
/resources/:resource/actions/:action
```

例如，停止某个运行的资源可以这么表示:

```path
/runs/{run_id}/actions/stop
```

对集合的操作也应该尽量减少。在需要时，它们应该使用顶级行为路径来避免命名空间冲突，
并清楚地显示操作范围:

```path
/actions/:action/resources
```

例如，重启所有服务器可以这么表示:

```path
/actions/restart/servers
```

### 使用统一的资源路径格式

#### 路径与属性名使用小写

为了和域名命名规则保持一致，使用小写字母并用 `-` 分割路径名字，例如:

```url
service-api.com/users
service-api.com/app-setups
```

属性也使用小写字母，但是属性名要用下划线 `_` 分割，以便在 JavaScript 中省略引号，例如:

```json
service_class: "first"
```

#### 支持无 ID 间接引用

某些情况下，用户无法方便地提供 ID 去定位资源。例如，一个用户想获取他在 Heroku 平台某个 app
的信息，但是这个 app 的唯一标识是 UUID。这种情况下就要支持接口通过名称和 ID 都能访问，例如:

```sh
curl https://service.com/apps/{app_id_or_name}
curl https://service.com/apps/97addcf0-c182
curl https://service.com/apps/www-prod
```

不要只接受名称而不支持 ID。

#### 最小化路径嵌套

在一些有父路径/子路径嵌套关系的资源中，路径可能有非常深的嵌套关系，例如:

```path
/orgs/{org_id}/apps/{app_id}/dynos/{dyno_id}
```

推荐优先将资源放置在根 (root) 路径下来减少路径的嵌套深度，嵌套用来指定有范围的集合资源。
在上述例子中，dyno 属于某个 app，app 属于某个 org 可以表示为:

```path
/orgs/{org_id}
/orgs/{org_id}/apps
/apps/{app_id}
/apps/{app_id}/dynos
/dynos/{dyno_id}
```

## 响应 (Responses)

响应部分概述了 API 响应的模式。

### 返回适当的状态码

为每一个响应返回适当的 HTTP 状态码。成功的响应应该使用如下的状态码:

- `200`: `GET`, `PUT`, `DELETE` 或 `PATCH` 请求同步地成功完成
- `201`: `POST` 请求同步地完成一个新资源的创建，
  在响应中提供指向新创建资源的 `Location` Header 也是最佳实践。这在 `POST`
  上下文中特别有用，因为新的资源具有与原请求不同的 URL。
- `202`: `POST`, `PUT`, `DELETE` 或 `PATCH` 请求被接受，且将被异步地处理
- `206`: `GET` 请求成功，但是只返回一部分，
  参考上文中的[通过请求中的范围 (Range) 拆分大的响应](#通过请求中的范围-range-拆分大的响应)部分

使用身份认证 (authentication) 和授权 (authorization) 错误码时需要注意:

- `401 Unauthorized`: 用户未认证，请求失败
- `403 Forbidden`: 用户无权限访问该资源，请求失败

返回适当的状态码可以提供额外的错误信息:

- `422 Unprocessable Entity`: 请求被服务器正确解析，但是包含无效字段
- `429 Too Many Requests`: 因为访问频繁，已经被限制访问，稍后重试
- `500 Internal Server Error`: 服务器内部错误，请确认服务状态或反馈该问题

对于用户错误和服务器错误的相关状态码，请参考 [HTTP response code spec](https://tools.ietf.org/html/rfc7231#section-6)

### 提供全部可用的资源

尽可能在响应中提供完整的资源表示 (例如: 某个对象的所有属性)。当响应码为 200 或是 201
时返回对应的完整资源，包括 `PUT`, `PATCH` 和 `DELETE` 请求，例如:

```sh
$ curl -X DELETE \  
  https://service.com/apps/1f9b/domains/0fd4

HTTP/1.1 200 OK
Content-Type: application/json;charset=utf-8
...
{
  "created_at": "2012-01-01T12:00:00Z",
  "hostname": "subdomain.example.com",
  "id": "01234567-89ab-cdef-0123-456789abcdef",
  "updated_at": "2012-01-01T12:00:00Z"
}
```

当请求状态码为 202 时，不返回完整的资源表示，例如:

```sh
$ curl -X DELETE \  
  https://service.com/apps/1f9b/dynos/05bd

HTTP/1.1 202 Accepted
Content-Type: application/json;charset=utf-8
...
{}
```

### 为资源提供 (UU)ID

默认情况下每个资源都应该有一个 `id` 属性。除非有更好的理由，否则请使用 UUID。
不要使用那种在不同服务或是资源中不是全局唯一的标识，尤其是自增 ID。

使用小写的 UUID 格式 `8-4-4-4-12`，例如:

```json
"id": "01234567-89ab-cdef-0123-456789abcdef"
```

<details>
  <summary>UUID?</summary>

---

> - <https://en.wikipedia.org/wiki/Universally_unique_identifier>
> - <https://www.quora.com/Has-there-ever-been-a-UUID-collision>

**Universally Unique IDentifier**.

A **universally unique identifier (UUID)** is a 128-bit label used for
information in computer systems. The term **globally unique identifier (GUID)**
is also used.

Q: *Has there ever been a UUID collision*?

A: Yes, see this [account of frequent UUID4 collisions](https://github.com/ramsey/uuid/issues/80).
> We are generating about 1M UUID4 a day, and we are getting several hundred
> collisions a day

The collisions occurred due to bugs in the underlying software, not due to
pure random chance. The problem appears to be with forked threads and OpenSSL.

Q: *UUID4*?

A: **UUID Version 4**, a version 4 UUID is randomly generated.

The number of random version-4 UUIDs which need to be generated in order to
have a 50% probability of at least one collision is 2.71 quintillion, computed
as follows:

![50% probability of at least one collision](images/uuid4_collision.svg)

</details>

### 提供标准的时间戳

为资源提供默认的创建时间 `created_at` 和更新时间 `updated_at`，例如:

```json
{
  ...
  "created_at": "2012-01-01T12:00:00Z",
  "updated_at": "2012-01-01T13:00:00Z",
  ...
}
```

时间戳对于某些资源没有任何意义，此时可以省略。

### 提供标准的响应数据类型

本文档描述了 JSON 基本数据类型的可接受值。

#### String

- 可接受值:
  - string
  - `null`

例如:

```json
[
  {
    "description": "very descriptive description."
  },
  {
    "description": null
  },
]
```

#### Boolean

- 可接受值:
  - `true`
  - `false`

例如:

```json
[
  {
    "provisioned_licenses": true
  },
  {
    "provisioned_licenses": false
  },
]
```

#### Number

- 可接受值:
  - number
  - `null`

注意: 有些 JSON 解析器会把精度超过 15 的小数位作为字符串返回。在需要的精度大于 15 位小数时，
该字段应始终返回一个字符串。否则，将这些字符串统一转换为数字，使 API 用户始终知道期望的值类型。

例如:

```json
[
  {
    "average": 27.123
  },
  {
    "average": 12.123456789012
  },
]
```

#### Array

- 可接受值:
  - array

注意: 当数组中没有值时，应返回一个空数组而不是 `null`。

例如:

```json
[
  {
    "child_ids": [1, 2, 3, 4],
  },
  {
    "child_ids": [],
  }
]
```

#### Object

- Acceptable values:
  - object
  - null

例如:

```javascript
[
  {
    "name": "service-production",
    "owner": {
      "id": "5d8201b0..."
     }
  },
  {
    "name": "service-staging",
    "owner": null
  }
]
```

### 使用 ISO8601 格式的 UTC (Coordinated Universal Time) 时间

仅接受和返回 UTC 时间，并以 ISO8601 格式表示，例如:

```json
"finished_at": "2012-01-01T12:00:00Z"
```

<details>
  <summary>2012-01-01T12:00:00Z</summary>

- `T`: 分隔符，前面是日期，后面是时间，且时间为 24 小时制
- `Z`: Offset of Zero，也就是零时区

</details>

### 嵌套外键关系

使用嵌套对象序列化外键关联，例如:

```json
{
  "name": "service-production",
  "owner": {
    "id": "5d8201b0..."
  },
  // ...
}
```

而不是:

```json
{
  "name": "service-production",
  "owner_id": "5d8201b0...",
  ...
}
```

这种方式尽可能地把相关联的资源信息内联在一起，而不用改变资源的结构，或者导致引入更多的顶层字段，
例如:

```json
{
  "name": "service-production",
  "owner": {
    "id": "5d8201b0...",
    "name": "Alice",
    "email": "alice@heroku.com"
  },
  ...
}
```

嵌套外键关系时，使用完整记录或仅使用外键。提供字段子集可能会导致意外和混乱，
使不同操作和端点之间的不一致更有可能发生。

为避免不一致和混淆，请选用其中一种方式序列化:

- 仅**外键**: 可以是 `id`, `slug`, `email` 等唯一标识字段.
- **完整记录**: 所有字段，也就是一个完整的内嵌记录。

### 生成结构化的错误

响应错误时，生成统一的、结构化的错误信息。包含一个机器可读的错误 `id`，一个人类可读的错误信息
(`message`)，根据情况可以添加一个 `url` 来告诉客户端关于这个错误的更多信息以及如何解决它，
例如:

```http
HTTP/1.1 429 Too Many Requests
```

```json
{
  "id":      "rate_limit",
  "message": "Account reached its API rate limit.",
  "url":     "https://docs.service.com/rate-limits"
}
```

提供错误信息格式及客户端可能遇到的错误 `id` 的相关文档。

### 显示频率限制状态

限制客户端的访问频次来维护服务器的良好状态，并为其他客户端提供高可用的服务。你可以使用
[token bucket algorithm](http://en.wikipedia.org/wiki/Token_bucket)
来量化请求限制。

在响应的 `RateLimit-Remaining` Header 中返回请求 token 的剩余可用数量。

<details>
  <summary>插播 Circuit Breaker</summary>

---

> [nodeshift/opossum](https://github.com/nodeshift/opossum)

```js
const CircuitBreaker = require('opossum');

function asyncFunctionThatCouldFail(x, y) {
  return new Promise((resolve, reject) => {
    // Do something, maybe on the network or a disk
  });
}

const options = {
  // If our function takes longer than 3 seconds, trigger a failure
  timeout: 3000, 

  // When 50% of requests fail, trip the circuit
  errorThresholdPercentage: 50,

  // After 30 seconds, try again.
  resetTimeout: 30000
};
const breaker = new CircuitBreaker(asyncFunctionThatCouldFail, options);

breaker.fire(x, y)
  .then(console.log)
  .catch(console.error);
```

</details>

### 保持响应 JSON 最小化

请求中多余的空白符会增加响应大小，而且现在很多 HTTP 客户端都会自己输出人类可读 ("prettify")
的 JSON。所以最好保持响应 JSON 最小化，例如:

```json
{"beta":false,"email":"alice@heroku.com","id":"01234567-89ab-cdef-0123-456789abcdef","last_login":"2012-01-01T12:00:00Z","created_at":"2012-01-01T12:00:00Z","updated_at":"2012-01-01T12:00:00Z"}
```

而不是这样:

```json
{
  "beta": false,
  "email": "alice@heroku.com",
  "id": "01234567-89ab-cdef-0123-456789abcdef",
  "last_login": "2012-01-01T12:00:00Z",
  "created_at": "2012-01-01T12:00:00Z",
  "updated_at": "2012-01-01T12:00:00Z"
}
```

也可以提供可选的方式为客户端提供更详细可读的响应，可以使用查询参数 (例如: `?pretty=true`)
或通过 `Accept` 头信息参数
(例如: `Accept: application/vnd.heroku+json; version=3; indent=4;`)。

## 工件 (Artifacts)

工件部分描述了用来管理和讨论 API 设计与模式的物理对象。

### 提供机器可读的 JSON Schema

提供一个机器可读的模式来准确表达你的 API。使用 [prmd](https://github.com/interagent/prmd)
来管理 Schema，并且确保用 `prmd verify` 验证是有效的。

### 提供人类可读的文档

提供人类可读的文档使客户端开发人员能够理解你的 API。

如果你安装以上的描述用 `prmd` 创建了一个 Schema，
那么你使用 `prmd doc` 方便地为所有端点 (API) 生成 Markdown 文档。

除了端点信息，提供一个所有 API 的概述信息:

- 验证授权，包含如何获取与如何使用 token。
- API 稳定性及版本信息，包含如何选择所需要的版本。
- 请求和响应的头信息。
- 错误信息的序列化格式。
- 不同编程语言客户端的 API 使用例子。

### 提供可执行的例子

提供可执行的示例让用户可以直接在终端里面观察 API 的调用情况，
最大程度地让这些示例可以方便地使用，以减少用户尝试使用 API 的工作量。例如:

```sh
export TOKEN=... # acquire from dashboard
curl -is https://$TOKEN@service.com/users
```

如果你使用 [prmd](https://github.com/interagent/prmd) 生成 Markdown 文档，
每个端点可以自动生成一些示例。

### 描述稳定性

根据成熟度与稳定性来描述 API 或具体端点的稳定性，例如: 加上原型 (prototype) / 开发版
(development) / 产品版 (production) 等标记。

更多关于可能的稳定性和变更管理的方式，请查看 [Heroku API compatibility policy](https://devcenter.heroku.com/articles/api-compatibility-policy)

一旦你的 API 以正式版本及稳定版本发布，不要在当前 API 版本中做出任何不兼容的变更。
如果确实需要，请创建一个新版本的 API。

<details>
  <summary>参考资料与扩展阅读</summary>

## 参考资料

- [HTTP API 设计指南](https://github.com/ZhangBohan/http-api-design-ZH_CN)
  - 英文原版: [HTTP API Design Guide](https://github.com/interagent/http-api-design)

## 扩展阅读

- [Microsoft REST API Guidelines](https://github.com/microsoft/api-guidelines)
- [An Architect's guide to APIs: SOAP, REST, GraphQL, and gRPC](https://www.redhat.com/architect/apis-soap-rest-graphql-grpc)
- [GraphQL](https://graphql.org/)
  - [How to GraphQL](https://www.howtographql.com/)
  - [GitHub GraphQL API](https://docs.github.com/cn/graphql)

</details>
