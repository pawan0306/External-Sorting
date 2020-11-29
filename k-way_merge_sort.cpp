#include <iostream>
#include <string.h>
using namespace std;

void merge(int *suff, long l, long m, long r){ 
    long n1=m-l+1; 
    long n2=r-m; 
    int *tempL=new int[n1];
    int *tempR=new int[n2]; 
    for(long i=0; i<n1; i++) 
        tempL[i]=suff[l+i]; 
    for(long j=0; j<n2; j++) 
        tempR[j]=suff[m+1+j]; 
    long i=0;
    long j=0;
    long k=l;  
    while(i<n1 && j<n2){ 
        if(tempL[i]<=tempR[j]){ 
            suff[k]=tempL[i]; 
            i++; 
        } 
        else{ 
            suff[k]=tempR[j]; 
            j++; 
        } 
        k++; 
    } 
    while(i<n1){ 
        suff[k]=tempL[i]; i++; k++; 
    } 
    while(j<n2){ 
        suff[k]=tempR[j]; j++; k++; 
    } 
    free(tempL);
    free(tempR);
} 
void sort(int *suff, long l, long r){ 
    if (l<r){ 
        long m=l+(r-l)/2; 
        sort(suff, l, m); 
        sort(suff, m+1, r); 
        merge(suff, l, m, r); 
    } 
}

int main(){
    FILE* f_fd;
    FILE* chunks[1000];
    string in_file;
    string out_file;
    string tmp_fle="temp_";
    cin>>in_file;
    cin>>out_file;
    long pieces=0;
    int* values= new int[1000000];
    f_fd=fopen(in_file.c_str(),"r");
    long i=0;
    while(!feof(f_fd)){
        fscanf(f_fd,"%d,",&values[i]);
        i++;
        if(i==1000000){
            sort(values,0,999999);
            long j=0;
            chunks[pieces]=fopen((tmp_fle+to_string(pieces)).c_str(),"w+");
            while(j<i){
                fprintf(chunks[pieces],"%d,",values[j]);
                j++;
            }
            i=0;
            chunks[pieces]=fopen((tmp_fle+to_string(pieces)).c_str(),"r");
            pieces++;
        }
    }
    if(i<=999999){
        sort(values,0,i);
        long j=0;
        chunks[pieces]=fopen((tmp_fle+to_string(pieces)).c_str(),"w+");
        while(j<i){
            fprintf(chunks[pieces],"%d,",values[j]);
            j++;
        }
        chunks[pieces]=fopen((tmp_fle+to_string(pieces)).c_str(),"r");
        pieces++;
    }
    fclose(f_fd);
    free(values);
    long len=10000;
    values=new int[10000*pieces];
    FILE* out=fopen(out_file.c_str(),"a+");
    for(i=0;i<200;i++){
        long k=0;
        for(long j=0;j<pieces;j++){
            long l=0;
            while(!feof(chunks[j]) && l<len){
                fscanf(chunks[j],"%d,",&values[k]);
                l++;
                k++;    
            }
        }
        sort(values,0,k-1);
        long tmp=0;
        while(tmp<k){
            fprintf(out,"%d,",values[tmp]);
            tmp++;
        }
    }
    int p=0;
    while(p<pieces){
        remove((tmp_fle+to_string(p)).c_str());
        p++;
    }
    remove(in_file.c_str());
}
