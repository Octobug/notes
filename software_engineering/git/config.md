# Git Config

## Customizing configs for different repos

For most git users, different git configs for different repos are desired.
Here comes a way to get it done once and for ever.

```sh
$ cd ~ && tree -La 2
.
├── .gitconfig
└── company
    └── .gitconfig
```

For example, for the user profile case:

- `.gitconfig`: git config under user scope

  ```config
  [user]
  name = YourUsername
  email = YourUsername@email.com

  [includeIf "gitdir:~/company/"]
  path = ~/company/.gitconfig
  ```

- `company/.gitconfig`: git config for specific repos under `company` directory

  ```config
  [user]
  name = YourUsernameForCompany
  email = YourEmailForCompany@company.com
  ```

To check if it works:

```sh
$ cd ~/company/any_repo && git config user.name
YourUsernameForCompany

$ git config user.email
YourEmailForCompany@company.com
```
