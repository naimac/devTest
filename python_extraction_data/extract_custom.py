import re, csv, os
from bs4 import BeautifulSoup

		# os.walk
		# os.readir

def scrapper(file_fullpath):
	# with open("50_268.html") as fp:
	with open(file_fullpath, 'r') as fp:
		soup = BeautifulSoup(fp, "lxml")

		error_code = soup.title.string
		list_content = soup.find_all(class_='pStandard')
		list_header= soup.find_all(class_='pUeberschrift3')
		list_param = soup.find_all(class_='pTabelle_Standard')

		max_column = len(list_content) + len(list_header) + len(list_param)
		print(f"max_column [{max_column}]")

		param_count = len(soup.find_all('tr'))

		return list_content, list_header, list_param, param_count, error_code, max_column

def csvHeaderFiller(list_header, list_len):

	header = []
	
	header.append('msg_id')
	header.append('msg_object')

	endColumn = ""

	for i in range(list_len):
		if (list_header[i].get_text() != "Parameter:"):
			header.append(list_header[i].get_text()[0:-1])
		else:
			endColumn = list_header[i].get_text()[0:-1]

	header.append(endColumn)

	return header

def csvParamFiller(list_param, header_len):

	row = []

	param_len = len(list_param)

	for i in range(header_len + 1):
		row.append('')

	for i in range(param_len - 1):
		if (i % 2 == 0):
			row.append(list_param[i].get_text() + list_param[i+1].get_text())
	return row

def csvFiller(html_file, writer):
	list_content, list_header, list_param, param_count, error_code = scrapper(html_file)
	header_len = len(list_header)

	header = csvHeaderFiller(list_header, header_len)
	writer.writerow(header)

	row = csvParamFiller(list_param, header_len)

	j = 0
	row[j] = error_code

	for i in range(len(list_content)):
		j = i + 1
		row[j] = list_content[i].get_text()

	writer.writerow(row)

def main():
	for (root, dirs, files) in os.walk("./html"):
		for filename in files:
			if filename.endswith(".html"):
				with open("msg_scrap.csv", "a") as output_file:
					writer = csv.writer(output_file, delimiter=";")
					csvFiller(os.path.abspath(os.path.join("./html", filename)), writer)
			# print(os.path.abspath(os.path.join("./html", filename)))
#  csvFiller("./html")

if __name__ == "__main__":
	main()