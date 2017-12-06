import idcpar

inParFile = '/home/local/kianicka/repositories/prj_2013_ctbto_autoshi_dacs4_impl/config/app_config/distributed/send_rabbit/send_rabbit.par'

idcparInst = idcpar.getpar()
# Prints current environment variables
idcparInst.printAll()

idcparInst.readParFile(inParFile)
#Test of some parameters
print "--------- a few test parameters ------"
if idcparInst.hasKey('hostname'):
    print "RABBITMQ_HOSTNAME: %s"%(idcparInst.getVal('hostname'))
if idcparInst.hasKey("EXPERTDB"):
    print "EXPERTDB: %s"%(idcparInst.getVal("EXPERTDB"))