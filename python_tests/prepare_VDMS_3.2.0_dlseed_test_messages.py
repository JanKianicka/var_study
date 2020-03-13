# This is one time script to generate more comprehensive test set of dlseed which has many bundled issues.
# Wrapper is poorly implemented and also stations have various issues.
import os

if __name__ == "__main__":
#     staInfoType = "DLSEED"
#     staInfoMsgIdB = "dlseed"
    staInfoType = "SC3XML"
    staInfoMsgIdB = "sc3xml"
    inputText = "BEGIN IMS2.0 \n\
MSG_TYPE REQUEST \n\
MSG_ID %s \n\
STA_LIST %s \n\
CHAN_LIST * \n\
STA_INFO IMS2.0:%s \n\
STOP"
    for ch in [chr(i) for i in range(ord('A'),ord('Z')+1)]:
        
        newMsgId = "%s_%s1"%(staInfoMsgIdB,ch)
        msg_text = inputText%(newMsgId, "%s*"%ch, staInfoType)
        requestOut = open(os.path.join("/home/kianicka/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsDlseed3.2.0","%s.msg"%(newMsgId)),"w")
        requestOut.write(msg_text)
        requestOut.close()
        
    representativeStations = ('AAK', 'AK07', 'AKASG', 'BATI', 'BOSA', 'CTA', 'CM06', 'DAV', 'DLI01', 'ESDC', 'ES01', 'FINES', 'FRB', 'FIC2', 
                              'GEYT', 'GUMO', 'GYA1', 'HFS', 'H11S1', 'H09W' )
    
    
        
    