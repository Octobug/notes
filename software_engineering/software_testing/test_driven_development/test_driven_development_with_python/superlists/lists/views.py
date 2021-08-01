from django.contrib.auth import get_user_model
from django.shortcuts import redirect, render
from django.views.generic import CreateView, DetailView, FormView

from lists.forms import ExistingListItemForm, ItemForm, NewListForm
from lists.models import List

User = get_user_model()


def my_lists(request, email):
    owner = User.objects.get(email=email)
    return render(request, 'my_lists.html', {'owner': owner})


class HomePageView(FormView):
    template_name = 'home.html'
    form_class = ItemForm


def home_page(request):
    return render(request, 'home.html', {'form': ItemForm()})


class ViewAndAddToList(CreateView, DetailView):
    model = List
    template_name = 'list.html'
    form_class = ExistingListItemForm

    def get_form(self, form_class=None):
        self.object = self.get_object()
        return self.form_class(for_list=self.object, data=self.request.POST)


def view_list(request, list_id):
    list_ = List.objects.get(id=list_id)
    form = ExistingListItemForm(for_list=list_)
    if request.method == 'POST':
        form = ExistingListItemForm(for_list=list_, data=request.POST)
        if form.is_valid():
            form.save()
            return redirect(list_)
    return render(request, 'list.html', {'list': list_, "form": form})


class NewListView(CreateView, HomePageView):
    form_class = NewListForm

    def form_valid(self, form):
        list_ = form.save(owner=self.request.user)
        return redirect(list_)


def new_list(request):
    form = NewListForm(data=request.POST)
    if form.is_valid():
        list_ = form.save(owner=request.user)
        return redirect(list_)
    return render(request, 'home.html', {'form': form})


def share_list(request, list_id):
    list_ = List.objects.get(pk=list_id)
    list_.shared_with.add(request.POST['sharee'])
    return redirect(list_)
