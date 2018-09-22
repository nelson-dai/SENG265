
import re,sys


tablenum=1

table_string=''

for line in sys.stdin:
    table_string+=line


tables= re.findall('<table.*?>.*?</table\s*>',table_string,re.DOTALL|re.I)
'''
for t in tables:
    print(t)
    print('----------------------------------')
'''

def patch_columns(data,ncols):
    for row in data:
        while len(row)<ncols:
            row.append('')

for table in tables:
    rows=re.findall('<tr.*?>.*?</tr\s*>',table,re.DOTALL|re.I)
    header,other_rows=rows[0],rows[1:]
    ncols=0
    header_pat='<th.*?>(.*?)</th\s*>'
    header_cols=re.findall(header_pat,header,re.DOTALL|re.I)
    #print(header_cols)
    data=[[]]
    ncols=len(header_cols)
    for col in header_cols:
        #m=re.search(header_pat,col,re.DOTALL|re.I)
        data[-1].append(re.sub('\s+',' ',col.strip()))
    ot_pat='<td.*?>(.*?)</td\s*>'
    for row in other_rows:
        data.append([])
        the_cols=re.findall(ot_pat,row,re.DOTALL|re.I)
        ncols=max(ncols,len(the_cols))
        for col in the_cols:
            #m=re.search(ot_pat,col,re.DOTALL|re.I)
            data[-1].append(re.sub('\s+',' ',col.strip()))
    patch_columns(data,ncols)
    print('TABLE %d:'%tablenum)
    print ('\n'.join(( ','.join(row)  for row in data)))
    print()
    tablenum+=1


'''
def read_table():
    html=''
    begin=False
    for line in sys.stdin:
        if not begin:
            if re.search('<table.*>',line):
                begin=True
                html+=line
        else:
            html+=line
            if re.search('</table\s*>',line):
                break
    return html
'''
