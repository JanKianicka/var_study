# This is one time script to generate more comprehensive test set of dlseed which has many bundled issues.
# Wrapper is poorly implemented and also stations have various issues.
import os

if __name__ == "__main__":
#     staInfoType = "DLSEED"
#     staInfoMsgIdB = "dlseed"
    staInfoType = "SC3XML"
    staInfoMsgIdB = "sc3xml"
    inputText = "BEGIN IMS2.0\n\
MSG_TYPE REQUEST\n\
MSG_ID %s\n\
TIME 2019-01-01 00:00:00 TO 2019-01-02 00:00:00\n\
STA_LIST %s\n\
CHAN_LIST *\n\
STA_INFO IMS2.0:%s\n\
STOP"
    for ch in [chr(i) for i in range(ord('A'),ord('Z')+1)]:
        
        newMsgId = "%s_%sall"%(staInfoMsgIdB,ch)
        msg_text = inputText%(newMsgId, "%s*"%ch, staInfoType)
        #requestOut = open(os.path.join("/home/kianicka/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsDlseed3.2.0","%s.msg"%(newMsgId)),"w")
        requestOut = open(os.path.join("/home/Jan/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsDlseed3.2.0","%s.msg"%(newMsgId)),"w")
        requestOut.write(msg_text)
        requestOut.close()
        
    representativeStations = ('AAK', 'AK07', 'AKASG', 'BATI', 'BOSA', 'CTA', 'CM06', 'DAV', 'DLI01', 'ESDC', 'ES01', 'FINES', 'FRB', 'FIC2', 
                              'GEYT', 'GUMO', 'GYA1', 'HFS', 'H11S1', 'H09W', 'I55US', 'INK', 'JAY', 'JPX38', 'JTS', 'KAPI', 'KBZ', 'KUR07',
                              'LBTB', 'LPAZ', 'LZB3', 'MATP', 'MK07', 'MSKU', 'MYP42', 'NOA', 'NV04', 'NVIAR', 'OPO', 'PAY50', 'PETK', 'PPT',
                              'RAO', 'RUP60', 'S2A4', 'SADO', 'TEIG', 'TOA0', 'TXAR', 'UKR05', 'USHA', 'VNDA', 'VIP00', 'ZAA0B', 'ZAL', 'ZALV' )
    
    for sta in representativeStations:
        newMsgId = "%s_%s"%(staInfoMsgIdB,sta)
        msg_text = inputText%(newMsgId, "%s"%sta, staInfoType)        
        requestOut = open(os.path.join("/home/Jan/projects/VDMS/smokeTestsAcceptanceTests/MailRequestsDlseed3.2.0","%s.msg"%(newMsgId)),"w")
        requestOut.write(msg_text)
        requestOut.close()
                
    
        
    