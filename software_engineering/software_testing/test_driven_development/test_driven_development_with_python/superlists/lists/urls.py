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
from django.urls import path
from lists import views

urlpatterns = [
    path('new', views.NewListView.as_view(), name='new_list'),
    path('<int:pk>/', views.ViewAndAddToList.as_view(), name='view_list'),
    path('users/<str:email>/', views.my_lists, name='my_lists'),
    path('<int:list_id>/share', views.share_list, name='share_list')
]
