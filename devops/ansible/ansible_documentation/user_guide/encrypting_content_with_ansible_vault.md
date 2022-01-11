# Encrypting content with Ansible Vault

> <https://docs.ansible.com/ansible/latest/user_guide/vault.html>

## Table of Contents

- [Encrypting content with Ansible Vault](#encrypting-content-with-ansible-vault)
  - [Table of Contents](#table-of-contents)
  - [Managing vault passwords](#managing-vault-passwords)
    - [Choosing between a single password and multiple passwords](#choosing-between-a-single-password-and-multiple-passwords)
    - [Managing multiple passwords with vault IDs](#managing-multiple-passwords-with-vault-ids)
      - [Limitations of vault IDs](#limitations-of-vault-ids)
      - [Enforcing vault ID matching](#enforcing-vault-id-matching)
    - [Storing and accessing vault passwords](#storing-and-accessing-vault-passwords)
      - [Storing passwords in files](#storing-passwords-in-files)
      - [Storing passwords in third-party tools with vault password client scripts](#storing-passwords-in-third-party-tools-with-vault-password-client-scripts)
  - [Encrypting content with Ansible Vault details](#encrypting-content-with-ansible-vault-details)
    - [Encrypting individual variables with Ansible Vault](#encrypting-individual-variables-with-ansible-vault)
      - [Advantages and disadvantages of encrypting variables](#advantages-and-disadvantages-of-encrypting-variables)
      - [Creating encrypted variables](#creating-encrypted-variables)
      - [Viewing encrypted variables](#viewing-encrypted-variables)
    - [Encrypting files with Ansible Vault](#encrypting-files-with-ansible-vault)
      - [Advantages and disadvantages of encrypting files](#advantages-and-disadvantages-of-encrypting-files)
      - [Creating encrypted files](#creating-encrypted-files)
      - [Encrypting existing files](#encrypting-existing-files)
      - [Viewing encrypted files](#viewing-encrypted-files)
      - [Editing encrypted files](#editing-encrypted-files)
      - [Changing the password and/or vault ID on encrypted files](#changing-the-password-andor-vault-id-on-encrypted-files)
      - [Decrypting encrypted files](#decrypting-encrypted-files)
      - [Steps to secure your editor](#steps-to-secure-your-editor)
  - [Using encrypted variables and files](#using-encrypted-variables-and-files)
    - [Passing a single password](#passing-a-single-password)
    - [Passing vault IDs](#passing-vault-ids)
    - [Passing multiple vault passwords](#passing-multiple-vault-passwords)
    - [Using `--vault-id` without a vault ID](#using---vault-id-without-a-vault-id)
  - [Configuring defaults for using encrypted content](#configuring-defaults-for-using-encrypted-content)
    - [Setting a default vault ID](#setting-a-default-vault-id)
    - [Setting a default password source](#setting-a-default-password-source)
  - [When are encrypted files made visible?](#when-are-encrypted-files-made-visible)
  - [Format of files encrypted with Ansible Vault](#format-of-files-encrypted-with-ansible-vault)
    - [Ansible Vault payload format 1.1 - 1.2](#ansible-vault-payload-format-11---12)

## Managing vault passwords

### Choosing between a single password and multiple passwords

### Managing multiple passwords with vault IDs

Vault ID used in 3 ways:

- Pass it with `--vault-id` to the ansible-vault command when you create
  encrypted content
- Include it wherever you store the password for that vault ID
- Pass it with `--vault-id` to the `ansible-playbook` command when you run a
  playbook that uses content you encrypted with that vault ID

The vault ID is the last element before the encrypted content. In addition to
the label, you must provide a source for the related password. The source can
be a `prompt`, a `file`, or a `script`. The pattern looks like this:
`--vault-id label@source`.

You can use `--vault-id` by itself, with `--vault-password-file`, or with
`--ask-vault-pass`. The pattern is the same as when you create encrypted
content: include the label and the source for the matching password.

#### Limitations of vault IDs

Ansible does not enforce using the same password every time you use a
particular vault ID label. You can encrypt different variables or files with
the same vault ID label but different passwords. It is possible to use
different passwords with the same vault ID label on purpose.

#### Enforcing vault ID matching

By default the vault ID label is only a hint to remind you which password you
used to encrypt a variable or file. Ansible does not check that the vault ID in
the header of the encrypted content matches the vault ID you provide when you
use the content. Ansible decrypts all files and variables called by your
command or playbook that are encrypted with the password you provide. To check
the encrypted content and decrypt it only when the vault ID it contains matches
the one you provide with `--vault-id`, set the config option
`DEFAULT_VAULT_ID_MATCH`, each password is only used to decrypt data that was
encrypted with the same label.

### Storing and accessing vault passwords

Most users store them securely and access them as needed from within Ansible.
You have two options for storing vault passwords that work from within Ansible:
in **files**, or in a **third-party tool** (client script is needed) such as
the system keyring or a secret manager.

#### Storing passwords in files

To store a vault password in a file, enter the password as a string on a single
line in the file. Make sure the permissions on the file are appropriate. Do not
add password files to source control.

#### Storing passwords in third-party tools with vault password client scripts

Retrieve passwords from within Ansible using a vault password client script. To
create a vault password client script:

- Create a file with a name ending in either `-client` or
  `-client.EXTENSION`
- Make the file executable
- Within the script itself:
  - Print the passwords to standard output
  - Accept a `--vault-id` option
  - If the script prompts for data, send the prompts to standard error

Specify the script as the source within the `--vault-id` flag. For example:

```sh
ansible-playbook --vault-id dev@contrib/vault/vault-keyring-client.py
```

results in the execution as follow:

```sh
contrib/vault/vault-keyring-client.py --vault-id dev
```

## Encrypting content with Ansible Vault details

You can encrypt two types of content with Ansible Vault: `variables` and
`files`. Encrypted content created with `--vault-id` also contains the vault ID
label.

### Encrypting individual variables with Ansible Vault

#### Advantages and disadvantages of encrypting variables

You cannot rekey encrypted variables. Also, variable-level encryption only
works on variables. If you want to encrypt tasks or other content, you must
encrypt the entire file.

#### Creating encrypted variables

`ansible-vault encrypt_string`

- a source for the vault password
- the string to encrypt
- the name of the variable

The pattern:

```sh
ansible-vault encrypt_string <password_source> '<string_to_encrypt>' --name \
'<string_name_of_variable>'
```

#### Viewing encrypted variables

### Encrypting files with Ansible Vault

Ansible Vault can encrypt any structured data file used by Ansible, including:

- group variables files from inventory
- host variables files from inventory
- variables files passed to ansible-playbook with `-e @file.yml` or
  `-e @file.json`
- variables files loaded by `include_vars` or `vars_files`
- variables files in roles
- defaults files in roles
- tasks files
- handlers files
- binary files or other arbitrary files

Aspects:

#### Advantages and disadvantages of encrypting files

With file-level encryption the contents of files are no longer easy to access
and read. This may be a problem with encrypted tasks files.

#### Creating encrypted files

```sh
ansible-vault create --vault-id test@multi_password_file foo.yml
```

To create a new encrypted data file with the vault ID ‘my_new_password’
assigned to it and be prompted for the password:

```sh
ansible-vault create --vault-id my_new_password@prompt foo.yml
```

#### Encrypting existing files

```sh
ansible-vault encrypt foo.yml bar.yml baz.yml
```

To encrypt existing files with the ‘project’ ID and be prompted for the
password:

```sh
ansible-vault encrypt --vault-id project@prompt foo.yml bar.yml baz.yml
```

#### Viewing encrypted files

```sh
ansible-vault view foo.yml bar.yml baz.yml
```

#### Editing encrypted files

```sh
ansible-vault edit --vault-id pass2@vault2 foo.yml
```

#### Changing the password and/or vault ID on encrypted files

```sh
ansible-vault rekey foo.yml bar.yml baz.yml
```

To set a different ID for the rekeyed files, pass the new ID to
`--new-vault-id`. For example, to rekey a list of files encrypted with the
‘preprod1’ vault ID from the ‘ppold’ file to the ‘preprod2’ vault ID and be
prompted for the new password:

```sh
ansible-vault rekey --vault-id preprod1@ppold --new-vault-id preprod2@prompt \
  foo.yml bar.yml baz.yml
```

#### Decrypting encrypted files

```sh
ansible-vault decrypt foo.yml bar.yml baz.yml
```

#### Steps to secure your editor

> <https://docs.ansible.com/ansible/latest/user_guide/vault.html#steps-to-secure-your-editor>

## Using encrypted variables and files

### Passing a single password

To prompt for the password:

```sh
ansible-playbook --ask-vault-pass site.yml
```

To retrieve the password from the `/path/to/my/vault-password-file` file:

```sh
ansible-playbook --vault-password-file /path/to/my/vault-password-file site.yml
```

To get the password from the vault password client script
`my-vault-password-client.py`:

```sh
ansible-playbook --vault-password-file my-vault-password-client.py
```

### Passing vault IDs

You can also use the `--vault-id` option to pass a single password with its
vault label. This approach is clearer when multiple vaults are used within a
single inventory.

To prompt for the password for the ‘dev’ vault ID:

```sh
ansible-playbook --vault-id dev@prompt site.yml
```

To retrieve the password for the ‘dev’ vault ID from the `dev-password` file:

```sh
ansible-playbook --vault-id dev@dev-password site.yml
```

To get the password for the ‘dev’ vault ID from the vault password client
script `my-vault-password-client.py`:

```sh
ansible-playbook --vault-id dev@my-vault-password-client.py
```

### Passing multiple vault passwords

If your task or playbook requires multiple encrypted variables or files that
you encrypted with different vault IDs, you must use the `--vault-id` option,
passing multiple `--vault-id` options to specify the vault IDs (‘dev’, ‘prod’,
‘cloud’, ‘db’) and sources for the passwords (prompt, file, script). . For
example, to use a ‘dev’ password read from a file and to be prompted for the
‘prod’ password:

```sh
ansible-playbook --vault-id dev@dev-password --vault-id prod@prompt site.yml
```

By default the vault ID labels (dev, prod and so on) are only hints. Ansible
attempts to decrypt vault content with each password. The password with the
same label as the encrypted data will be tried first, after that each vault
secret will be tried in the order they were provided on the command line.

Where the encrypted data has no label, or the label does not match any of the
provided labels, the passwords will be tried in the order they are specified.
In the example above, the ‘dev’ password will be tried first, then the ‘prod’
password for cases where Ansible doesn’t know which vault ID is used to encrypt
something.

### Using `--vault-id` without a vault ID

The `--vault-id` option can also be used without specifying a vault-id. This
behavior is equivalent to `--ask-vault-pass` or `--vault-password-file` so is
rarely used.

For example, to use a password file `dev-password`:

```sh
ansible-playbook --vault-id dev-password site.yml
```

To prompt for the password:

```sh
ansible-playbook --vault-id @prompt site.yml
```

To get the password from an executable script `my-vault-password-client.py`:

```sh
ansible-playbook --vault-id my-vault-password-client.py
```

## Configuring defaults for using encrypted content

### Setting a default vault ID

[DEFAULT_VAULT_IDENTITY_LIST](https://docs.ansible.com/ansible/latest/reference_appendices/config.html#default-vault-identity-list)

### Setting a default password source

[DEFAULT_VAULT_PASSWORD_FILE](https://docs.ansible.com/ansible/latest/reference_appendices/config.html#default-vault-password-file)

## When are encrypted files made visible?

There is one exception. If you pass an encrypted file as the `src` argument to
the `copy`, `template`, `unarchive`, `script` or `assemble` module, the file
will not be encrypted on the target host (assuming you supply the correct vault
password when you run the play). This behavior is intended and useful. You can
encrypt a configuration file or template to avoid sharing the details of your
configuration, but when you copy that configuration to servers in your
environment, you want it to be decrypted so local users and processes can
access it.

## Format of files encrypted with Ansible Vault

> <https://docs.ansible.com/ansible/latest/user_guide/vault.html#format-of-files-encrypted-with-ansible-vault>

### Ansible Vault payload format 1.1 - 1.2

> <https://docs.ansible.com/ansible/latest/user_guide/vault.html#ansible-vault-payload-format-1-1-1-2>
