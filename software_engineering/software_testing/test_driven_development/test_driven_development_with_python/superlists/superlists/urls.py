"""superlists URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.urls import include, path
from lists import views as list_views
# from lists import api_urls
from lists.api import router
from lists import urls as list_urls
from accounts import urls as account_urls

urlpatterns = [
    path('', list_views.HomePageView.as_view(), name='home'),
    path('accounts/', include(account_urls)),
    # path('api/', include(api_urls)),
    path('api/', include(router.urls)),
    path('lists/', include(list_urls)),
]
