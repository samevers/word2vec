#! /usr/bin/python 
#encoding:gb18030
############################################
#
# Author: lichao
# Create time: 2014  2月 18 14时54分57秒
# E-Mail: lichaotx020@sogou-inc.com
# version 1.0
#
############################################

def strQ2B(ustring):
	"""把字符串全角转半角"""
	rstring = ""
	for uchar in ustring:
		inside_code=ord(uchar)
		if inside_code==0x3000:
			inside_code=0x0020
		else:
			inside_code-=0xfee0
		if inside_code<0x0020 or inside_code>0x7e:      #转完之后不是半角字符则返回原来的字符
			rstring += uchar
			continue
		rstring += unichr(inside_code)
	return rstring


def strB2Q(ustring):
	"""把字符串半角转全角"""
	rstring = ""
	for uchar in ustring:
		inside_code=ord(uchar)
		if inside_code<0x0020 or inside_code>0x7e:      #不是半角字符则返回原来的字符
			rstring += uchar
			continue
		if inside_code==0x0020: #除了空格其他的全角半角的公式为:半角=全角-0xfee0
			inside_code=0x3000
		else:
			inside_code+=0xfee0
		rstring += unichr(inside_code)
	return rstring

def GetEngWordNum(query):
	try:
		query = query.decode("gb18030")
		query = strQ2B(query)

		query = query.encode("gb18030")
	except:
		return []

	query = query.lower()
	eng_num = 0
	word_num = 0
	num_num = 0
	i = 0
	while i < len(query):
		if ord(query[i]) >= 128:
			 word_num += 1
			 i += 2
			 continue
		elif query[i] >= 'a' and query[i] <= 'z':
			 eng_num += 1
		elif query[i] >= '0' and query[i] <= '9':
			 num_num += 1
		i += 1
	array_result = [eng_num, word_num, num_num]
	return  array_result




