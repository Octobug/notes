from django.conf import settings
from selenium import webdriver

from .base import FunctionalTest
from .list_page import ListPage
from .my_lists_page import MyListsPage

SHARE_EMAIL = settings.SHARE_EMAIL


def quit_if_possible(browser):
    try:
        browser.quit()
    except:
        pass


class SharingTest(FunctionalTest):

    def test_can_share_a_list_with_another_user(self):
        # Edith is a logged-in user
        self.create_pre_authenticated_session(settings.TEST_EMAIL)
        edith_browser = self.browser
        self.addCleanup(lambda: quit_if_possible(edith_browser))

        # Her friend Oniciferous also uses the lists site
        oni_browser = webdriver.Firefox()
        self.addCleanup(lambda: quit_if_possible(oni_browser))
        self.browser = oni_browser
        self.create_pre_authenticated_session(SHARE_EMAIL)

        # Edith visits the home page, creates a new list
        self.browser = edith_browser
        list_page = ListPage(self).add_list_item('Get help')

        # She sees the "share the list" option
        share_box = list_page.get_share_box()
        self.assertEqual(
            share_box.get_attribute('placeholder'),
            'your-friend@example.com'
        )

        # She shared the list, page is refreshed
        # Showing that list has been shared
        list_page.share_list_with(SHARE_EMAIL)

        # Now Oniciferous visits his lists page
        self.browser = oni_browser
        MyListsPage(self).go_to_my_lists_page()

        # He sees the list shared by Edith
        self.browser.find_element_by_link_text('Get help').click()

        # In the list page, Oniciferous sees that the list belons to Edith
        self.wait_for(lambda: self.assertEqual(
            list_page.get_list_owner(),
            settings.TEST_EMAIL
        ))

        # He adds a item to this list
        list_page.add_list_item('Hi Edith!')

        # After Edith refresh the page, she sees the new item
        self.browser = edith_browser
        self.browser.refresh()
        list_page.wait_for_row_in_list_table('Hi Edith!', 2)
