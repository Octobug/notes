from fabric.contrib.files import append, exists, sed
from fabric.api import env, local, run
import random

REPO_URL = 'https://github.com/Octobug/tdd-python.git'
env.user = 'orca'
env.host = 'staging.tdd.com'


def deploy():
    site_folder = '/home/%s/app/%s' % (env.user, env.host)
    repo_folder = site_folder + '/repo'
    source_folder = site_folder + '/source'
    _create_directory_structure_if_necessary(site_folder)
    _get_latest_source(repo_folder, source_folder)
    _update_settings(source_folder, env.host)
    _update_virtualenv(repo_folder, source_folder)
    _update_static_files(source_folder)
    _update_database(source_folder)
    _restart_gunicorn(env.host)


def _restart_gunicorn(service):
    run(f'sudo systemctl restart {service}')


def _create_directory_structure_if_necessary(site_folder):
    for subfolder in ('database', 'static', 'venv', 'source'):
        run('mkdir -p %s/%s' % (site_folder, subfolder))


def _get_latest_source(repo_folder, source_folder):
    if exists(repo_folder + '/.git'):
        run('cd %s && git fetch' % (repo_folder,))
    else:
        run('git clone %s %s' % (REPO_URL, repo_folder))
    current_commit = local("git log -n 1 --format=%H", capture=True)
    run('cd %s && git reset --hard %s' % (repo_folder, current_commit))
    run('rm -rf %s' % (source_folder,))
    run('cp -rf %s/superlists %s' % (repo_folder, source_folder))


def _update_settings(source_folder, site_name):
    settings_path = source_folder + '/superlists/settings.py'
    sed(settings_path, "DEBUG = True", "DEBUG = False")
    sed(settings_path,
        'ALLOWED_HOSTS =.+$',
        'ALLOWED_HOSTS = ["%s"]' % (site_name,)
        )
    secret_key_file = source_folder + '/superlists/secret_key.py'
    if not exists(secret_key_file):
        chars = 'abcdefghijklmnopqrstuvwxyz0123456789!@#$%^&*(-_=+)'
        key = ''.join(random.SystemRandom().choice(chars) for _ in range(50))
        append(secret_key_file, "SECRET_KEY = '%s'" % (key,))
    append(settings_path, '\nfrom .secret_key import SECRET_KEY')


def _update_virtualenv(repo_folder, source_folder):
    virtualenv_folder = source_folder + '/../venv'
    if not exists(virtualenv_folder + '/bin/pip'):
        run('virtualenv %s' % (virtualenv_folder,))
    run('%s/bin/pip install -r %s/requirements.pip' % (
        virtualenv_folder, repo_folder
    ))


def _update_static_files(source_folder):
    run(f'cd {source_folder} && ../venv/bin/python manage.py '
        f'collectstatic --noinput')


def _update_database(source_folder):
    run(f'cd {source_folder} && ../venv/bin/python manage.py '
        f'migrate --noinput')
