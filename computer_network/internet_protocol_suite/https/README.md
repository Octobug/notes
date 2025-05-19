# HTTPS

## OpenSSL

### Windows Equivalent

```ps1
$URL = 'https://www.google'
$Connection = [System.Net.HttpWebRequest]::Create($URL)
$Response = $Connection.GetResponse()
$Response.Dispose()
$Certificate = $Connection.ServicePoint.Certificate
$Certificate.GetSerialNumberString()
$Certificate.GetExpirationDateString()
```

## References

- [howhttps.works](https://howhttps.works/)
