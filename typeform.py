from selenium import webdriver
from selenium.webdriver.common.keys import Keys
from time import sleep

###################################################################################

repeat = 5
url = 'https://ankitaa.typeform.com/to/pnmy8U'
answers = ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15']

###################################################################################

browser = webdriver.Chrome(executable_path = './chromedriver')
browser.implicitly_wait(10)
browser.maximize_window()

for i in xrange(repeat):

    browser.get(url)

    sleep(3)
    start = browser.find_element_by_xpath('//*[@id="330348"]/div[1]/div/div[3]/div[1]')
    start.click()

    sleep(2)
    inputs = browser.find_elements_by_tag_name('input')
    for i in xrange(len(inputs)):
        inputs[i].send_keys(answers[i])
        inputs[i].send_keys(Keys.RETURN)
        sleep(0.5)

    submit = browser.find_element_by_xpath('//*[@id="unfixed-footer"]/div[3]/div[1]/div[1]')
    submit.click()
    sleep(2)

browser.close()
