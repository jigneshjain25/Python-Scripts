#!/usr/bin/env python
from twisted.words.protocols import irc
from twisted.internet import protocol
from twisted.internet import reactor
import sys
class STirc(irc.IRCClient):
    def _get_nickname(self):
        return self.factory.nickname
    nickname = property(_get_nickname)

    def signedOn(self):
        for cha in self.factory.favchan:
            self.join(cha,'assignmnt')
        print "Signed on as %s." % (self.nickname,)        

    def joined(self, channel):        
        print "Joined %s." % (channel)
        #self.msg('NickServ','identify fake400')
        self.factory.spam_nick=self.factory.spam_nick+' ';
        for i in range(0,30):
            #self.msg('tan','tan'*i,200)
            self.say(channel,self.factory.spam_nick*i)
    
class STircFactory(protocol.ClientFactory):
    protocol = STirc

    def __init__(self,parent,nickname='twistedTrial'):        
        self.nickname = nickname
        self.parent = parent
        self.favchan = []

    def clientConnectionLost(self, connector, reason):
        print "Lost connection (%s), reconnecting." % (reason,)        
        connector.connect()

    def clientConnectionFailed(self, connector, reason):
        print "Could not connect: %s" % (reason,)    

    def setFavChannels(self,list):
        self.favchan = list

    def setSpamNick(self,spam_nic):
        self.spam_nick=spam_nic;


if __name__=="__main__":
    if len(sys.argv) != 4:
        print "Usage: \'python spammer.py nick_name channel_name spam_nick\'"
    else:
        factory = STircFactory(None,sys.argv[1])
        mylist = ['#'+sys.argv[2]]
        factory.setFavChannels(mylist)
        factory.setSpamNick(sys.argv[3])
        connector = reactor.connectTCP('irc.dejatoons.net',6667,factory)
        reactor.run()  

