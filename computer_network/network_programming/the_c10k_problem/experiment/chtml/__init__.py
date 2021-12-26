def render(tmpl_path, data={}):
    with open(tmpl_path, 'r') as f:
        tmpl = f.read()

    return tmpl.format(**data)
