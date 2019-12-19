# Auxiliary script to process request messages stripped out from acceptance tests of the new-message-subsystem repository.   
# Stored for convenience.
# JK. 19.12.2019 
import os
import re


def getMsgIdFromMessageBody(messageText):
    # MSG_ID can be in any letters - no case sensitivity in Fromats and Protocols
    msgIdPattern = "(([Mm][Ss][Gg]_[Ii][Dd]) (.*))"
    m = re.search(msgIdPattern, messageText)

    return m.group(3)

def replaceMsgIdWithNewSubject(msgId, subject, messageText):
    return re.sub(msgId, subject, messageText)

if __name__ == "__main__":
    requestF = open("/home/kianicka/projects/VDMS/smokeTestsAcceptanceTests/nmsRequests.txt", 'r').read()
    outDir = "/home/kianicka/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsAccept"
    i_begin = requestF.find("BEGIN")
    i_stop = requestF.find("STOP")
 
    print len(requestF)
    #exit(0)
    count = 0
    while i_stop+15<len(requestF):
        # print "ORIGINAL MATHC: %s\n\n"%requestF[i_begin:i_stop]
        msg_text = "%sSTOP"%requestF[i_begin:i_stop].strip().replace("  ","").replace("\r","").replace("\\n"," XXXXXX ").replace("\n","").replace("\\","").replace(" XXXXXX ","\n").replace("\" \"","")
        #print msg_text
        
        i_begin = requestF.find("BEGIN",i_begin+1)
        i_stop = requestF.find("STOP",i_stop+1)
        #print "\ni_begin, i_stop: %d, %d\n"%(i_begin, i_stop)
        newMsgId = "%s_%.3d"%(getMsgIdFromMessageBody(msg_text)[0:10].replace("%d","").replace("%s","").replace(" ",""), 
                              count)
        #print "MSG_ID: %s"%newMsgId
        print "\n"
        msg_text = replaceMsgIdWithNewSubject(getMsgIdFromMessageBody(msg_text), newMsgId, msg_text)
        msg_text = replaceMsgIdWithNewSubject("e-mail %s", "e-mail foo@bar.bar", msg_text)
        print msg_text
        requestOut = open(os.path.join("/home/kianicka/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsAccept","accept_msg_%s.msg"%(newMsgId)),"w")
        requestOut.write(msg_text)
        requestOut.close()
        
        count += 1
    print count
    
    