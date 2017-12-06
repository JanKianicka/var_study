'''
Playing a little with Jinja2 template package.

http://jinja.pocoo.org/docs/dev/api/#basics

'''

from jinja2 import Environment, PackageLoader
from jinja2.loaders import DictLoader

template_name = "SaunaArrHtml-v1.0.html"
env = Environment(loader=PackageLoader('jinja2_templates', 'templates'))
print dir(env)
#print env.__doc__
template = env.get_template(template_name)
print dir(template)
print template.__doc__
# Now the template can be rendered with a variable
html_out = template.render(report_type = "ARR")
# it is possible to render 
html_out2 = template.render({'report_type':"ARR"})
print html_out.find("ARR")
print html_out2.find("ARR")

# Now we test Dictonary loader
test_template2 = "<h1 style=\"text-align:center;\">IDC Generated Report \
<br/>{{report_type}} Radionuclide Report \
<br/>Noble Gas Version</h1>"

loader2 = DictLoader({'index.html': test_template2})
env2 = Environment(loader = loader2)
template2 = env2.get_template('index.html')

print template2.render({'report_type':u"ARR"})
