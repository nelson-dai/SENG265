import sys,os,csv

# Error message for arguement missing
if len(sys.argv) in [1,2]:
    print('Usage: python3 merge.py <key column name> <file 1> <file 2> <file 3> <file 4> ...',file=sys.stderr)
    sys.exit(1)

# Setting arguement for key and file names
key_column=sys.argv[1]
fnames=sys.argv[2:]

# Test if the files can be opened
def open_file(fname):
    try:
        fh=open(fname)
    except:
        print('Error: Unable to open %s'%fname,file=sys.stderr)
        sys.exit(1)
    return fh

fhandles=list(map(open_file,fnames))

# Reading values into data
def read_data(fname,fh):
    data=[]
    cr=csv.reader(fh)
    n=0
    for row in cr:
        row=list(map(lambda s: s.strip(),row))
        if row!=['']*len(row):
            data.append(row)
        else:
            continue
        if n and len(row)!=n:
            print('Inconsistent columns in "%s"'%fname,file=sys.stderr)
            sys.exit(1)
        n=len(row)
    fh.close()
    if not data:
        print('File "%s" contains no data'%fname,file=sys.stderr)
        sys.exit(1)
    return data


file_datas=[]

for fname,fh in zip(fnames,fhandles):
    file_datas.append(read_data(fname,fh))


# find and return a duplicate of a list 'cols' return none otherwise
def find_duplicate_column(cols):
    unique=[]
    for c in cols:
        if c in unique:
            return c
        unique.append(c)


# make a dictionary of the form {key_column_row:{column_name:column_value}}
def to_kv_dict(fname,data,kvcol):
    header=data[0]
    try:
        kvindex=header.index(kvcol)
    except ValueError:
        print('Error: File %s No column called "%s"'%(fname,kvcol),file=sys.stderr)
        sys.exit(1)
    colnames=header[:kvindex]+header[kvindex+1:]
    dup=find_duplicate_column(colnames)
    if dup!=None:
        print('Duplicate column "%s"'%dup,file=sys.stderr)
        sys.exit(1)
    valkeys={j:i for i,j in enumerate(header) if i!=kvindex}
    kvd=table_to_dict(data[1:],kvindex)
    return colnames,kvd

def table_to_dict(T, key_column_index):
    output_dict = {}
    for row in T:
        #print(row)
        key = row[key_column_index]
        rest_of_row = row[0:key_column_index] + row[key_column_index+1:]
        if key in output_dict:
            print('Duplicate key "%s"'%(key),file=sys.stderr)
            sys.exit(1)
        output_dict[key] = rest_of_row
    return output_dict

file_kvds=[]
colnames=[]

for fn,d in zip(fnames,file_datas):
    cns,kvd=to_kv_dict(fn,d,key_column)
    file_kvds.append(kvd)
    colnames.append(cns)

# merge multiple dictionaries into one dictionary.
def merge_dicts(kvds,cnames):
    merged={}
    size=sum((len(L) for L in cnames))
    merged_cnames=[]
    for c in cnames:
        merged_cnames.extend(c)
    cndict={j:i for i,j in enumerate(merged_cnames)}
    for cols,kvd in zip(cnames,kvds):
        for key in kvd:
            if key not in merged:
                merged[key]=[None]*size
            for (colname,colvalue) in zip(cols,kvd[key]):
                if merged[key][cndict[colname]]!=None:
                    print('Duplicate column "%s"'%colname,file=sys.stderr)
                    sys.exit(1)
                merged[key][cndict[colname]]=colvalue
    return merged,merged_cnames



merged,colnames=merge_dicts(file_kvds,colnames)



# vd is a dict with keys from colnames make into a list of values of vd
def get_list(colnames,vl):
    l=list(vl)
    for i,j in enumerate(l):
        if j==None:
            l[i]=''
    return l

# prints out the dictionary in csv format, given the key column, a list colnames, and a dictionary md of the form
# {key_column_row:{column_name:column_value}}.
def output_dict(keycol,colnames,md):
    print(','.join([keycol]+colnames))
    for key in sorted(md):
        print(','.join([key]+get_list(colnames,md[key])))

output_dict(key_column,colnames,merged)
