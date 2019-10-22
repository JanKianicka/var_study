# content of nosetest.py
# It is possible to run it from command line:
# nosetests -v nose_test.py
# and it will execute all asserts - like this we can verify some array of test results

def func(x):
    return x + 1
   
def func2(x):
    assert x
    
def test_answer():
    for i in [True, False, True, False]:
        yield (func2, i)
    
#     assert func(4) == 5
#     assert func(3) == 5
#     assert func(10) == 5
    