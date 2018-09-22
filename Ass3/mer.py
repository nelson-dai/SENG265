
import sys,os,csv

# A helper method for printing error message and exit the program 
def report_error(msg):
    print(msg,file=sys.stderr)
    sys.exit(1)

# Error message for arguement missing 
if len(sys.argv) in [1,2]:
    report_error('Usage: python3 merge.py <key column name> <file 1> <file 2> <file 3> <file 4> ...')

# Setting arguement for key and file names
key_column=sys.argv[1]
fnames=sys.argv[2:]

# Test if the files can be opened
def open_file(fname):
    try:
        fh=open(fname)
    except:
        report_error('Error: Unable to open %s'%fname)
    return fh

fhandles=list(map(open_file,fnames))

# Reading values into data
def read_data(fname,fh):
    data=[]
    cr=csv.reader(fh)
    n=0
    for row in cr:
        if row:
            data.append(list(map(lambda s: s.strip(),row)))
        if n and len(row)!=n:
            report_error('Inconsistent columns in "%s"'%fname)
        n=len(row)
    fh.close()
    if not data:
        report_error('File "%s" contains no data'%fname)
    return data


file_datas=[]

for fname,fh in zip(fnames,fhandles):
    file_datas.append(read_data(fname,fh))



def find_duplicate_column(cols):
    unique=[]
    for c in cols:
        if c in unique:
            return c
        unique.append(c)



def to_kv_dict(fname,data,kvcol):
    header=data[0]
    try:
        kvindex=header.index(kvcol)
    except ValueError:
        report_error('Error: File %s No column called "%s"'%(fname,kvcol))
    colnames=header[:kvindex]+header[kvindex+1:]
    dup=find_duplicate_column(colnames)
    if dup!=None:
        report_error('Duplicate column "%s"'%dup)
    valkeys={j:i for i,j in enumerate(header) if i!=kvindex}
    kvd={}
    for row in data[1:]:
        kvd[row[kvindex]]={}
        for v,i in valkeys.items():
            kvd[row[kvindex]][v]=row[i]
    return colnames,kvd

file_kvds=[]
colnames=[]

for fn,d in zip(fnames,file_datas):
    cns,kvd=to_kv_dict(fn,d,key_column)
    file_kvds.append(kvd)
    colnames.extend(cns)


def merge_dicts(kvds):
    merged={}
    for kvd in kvds:
        for key in kvd:
            if key not in merged:
                merged[key]={}
            for colname,colvalue in kvd[key].items():
                if colname in merged[key]:
                    report_error('Duplicate column "%s"'%colname)
                merged[key][colname]=colvalue
    return merged



merged=merge_dicts(file_kvds)

def get_list(colnames,vd):
    l=['']*(len(colnames))
    for i,j in enumerate(colnames):
        if j in vd:
            l[i]=vd[j]
    return l

def output_dict(keycol,colnames,md):
    print(','.join([keycol]+colnames))
    for key in sorted(md):
        print(','.join([key]+get_list(colnames,md[key])))


output_dict(key_column,colnames,merged)
