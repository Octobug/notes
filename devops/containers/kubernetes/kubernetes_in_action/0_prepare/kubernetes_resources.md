# Kubernetes resources

- `Resource (abbr.) [API version]`: `Description`

## Resources

- `Namespace* (ns) [v1]`: Enables organizing resources into non-overlaping
  groups (for example, per tenant)
- Deploying workloads
  - `Pod (po) [v1]`: The basic deployable unit containing one or more processes
    in co-located containers
  - `ReplicaSet (rs) [apps/v1beta2**]`: Keeps one or more pod replicas running
  - `ReplicationController (rc) [v1]`: The older, less-powerful equivalent of a
    ReplicaSet
  - `Job [batch/v1]`: Runs pods that perform a completable task
  - `CronJob [batch/v1beta1]`: Runs a scheduled job once or periodically
  - `DaemonSet (ds) [apps/v1beta2**]`: Runs one pod replica per node (on all
    nodes or only on those matching a node selector)
  - `StatefulSet (sts) [apps/v1beta1**]`: Runs stateful pods with a stable
    identity
  - `Deployment (deploy) [apps/v1beta1**]`: Declarative deployment and updates
    of pods
- Services
  - `Service (svc) [v1]`: Exposes one or more pods at a single and stable IP
    address and port pair
  - `Endpoints (ep) [v1]`: Defines which pods (or other servers) are exposed
    through a service
  - `Ingress (ing) [extensions/v1beta1]`: Exposes one or more services to
    external clients through a single externally reachable IP address
- Config
  - `ConfigMap (cm) [v1]`: A key-value map for storing non-sensitive config
    options for apps and exposing it to them
  - `Secret [v1]`: Like a ConfigMap, but for sensitive data
- Storage
  - `PersistentVolume* (pv) [v1]`: Points to persistent storage that can be
    mounted into a pod through a PersistentVolumeClaim
  - `PersistentVolumeClaim (pvc) [v1]`: A request for and claim to a
    PersistentVolume
  - `StorageClass* (sc) [storage.k8s.io/v1]`: Defines the type of
    dynamically-provisioned storage claimable in a PersistentVolumeClaim

> `*`: Cluster-level resource (not namespaced)
> `**`: Also in other API versions; listed version is the one used in this book
