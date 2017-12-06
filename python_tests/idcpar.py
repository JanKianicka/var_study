#!/usr/bin/python
# Program : getpar.py
# Purpose : Python program to read IDC par files
# Author : Shaban LABAN
#          Processing Systems Officer
#	   IDC/APS
# Date   :June 2012

'''
Copied from ibase/src/Archive/scripts/ for testing.
'''
import os
import os.path

class getpar(object):
	pars = {}
	parFile = ''

	def hasKey(self,key):
		return self.pars.has_key(key)

	def putVal(self,key,val):
		self.pars[key]=val
	
	def getVal(self,key):
		if key in self.pars:
			return self.pars[key]
		else:
			return ''
	
	def __getCleanLine(self,myline):
		cn= myline.find('#')
		if cn > 0:
			cLine=myline[:cn]
		else:
			cLine=myline
		return cLine

	def readParFile(self,fileName):
		if not os.path.exists(fileName):
			print "The parfile %s does not exist." % (fileName)
			return False
		self.parFile=fileName
		f = open(self.parFile, 'r')
		lines = f.readlines()
		myline=''
		f.close()
		for line in lines:
			# remove \n
			line=line.rstrip('\n')
			
			# exclude comments
			cS= line.find('#') 
			if cS >= 0:
				line=line[:cS]	
			
			if line == '':
				xyline=''
			elif line.endswith('\\'):
				myline += line[0:-1]		
			else:
				myline += line
				myline=myline.strip()
				myline=self.__getCleanLine(myline)
				eqS=myline.find('=')
				key=''
				val=''
				if eqS > 0:
					key=myline[:eqS]
					val=myline[eqS+1:]
				key=key.strip()
				val=val.strip()
				if key == 'par':
					newVal=self.__parseVal(val)
					self.readParFile(newVal)
				else:
					if key != '':
						newVal=self.__parseVal(val)
						self.pars[key]=newVal
				myline=''
		return True

	def __parseVal(self,strVal):
		tVal=strVal
		qS=strVal.find('"')
		if qS == 0:
			tVal=strVal[1:]
			l=len(tVal)-1
			zVal=tVal[:l]
			tVal=zVal
		else:
			q1S=strVal.find("'")
			if q1S == 0:
				tVal=tVal[1:]	
				tVal=tVal[:len(tVal)-1]
		vS=tVal.find('$')
		prefix=''
		rest=''
		suffex=''
		
		if vS >= 0:
			while (vS >= 0):
				#found $
				prefix=tVal[:vS]
				rest=tVal[vS+1:]
				o1S=rest.find('(')
				if o1S >= 0:
					rest=rest[o1S+1:]
					o1E=rest.find(')')
					if o1E >= 0:
						oo=rest				
						rest=oo[:o1E]
						suffex=oo[o1E+1:]
				if rest in self.pars:
					tVal=prefix+self.pars[rest]+suffex
				else:
					tVal=prefix+suffex
				vS=tVal.find('$')	
		
		return tVal

	def printAll(self):
		for key in self.pars.keys():
			print "%s : %s" % (key,self.pars[key])

	def __init__(self,*args ):
		self.parFile=''
		self.pars = {}
		
		if len(args) >= 1:
			self.parFile=args[0]
		if len(args) >= 2:
			self.pars = args[1]
		# read Env
		for param in os.environ.keys():
			self.pars[param]=os.environ[param]
		
		#if self.parFile == '':
		#	self.readParFile(self.parFile)
			
