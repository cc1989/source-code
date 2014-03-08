#set -o nounset                  # Treat unset variables as an error
PATH="/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin"
export PATH

#echo -n "input your project name:"
read -p "input your project name:" project_name 
echo $project_name
path="$(pwd)/${project_name}"
echo "now,mkdir $path"
mkdir $project_name
if [ "$?" != "0" ]
then
    exit 0
fi
cd $project_name
touch Makefile
if [ "$?" != "0" ]
then
    exit 0
fi

touch Makefile
if [ "$?" != "0" ]
then
    exit 0
fi

echo "ifneq (\$(KERNELRELEASE),)
    obj-m := $project_name.o
else
    OBJS = $project_name.c
    KERNELDIR ?= /lib/modules/\$(shell uname -r)/build
    PWD := \$(shell pwd)
default:
    \$(MAKE) -C \$(KERNELDIR) M=\$(PWD) modules
endif

.PHONY:clean
clean:
    find -path \"./*\" ! -path \"./\$(OBJS)\" ! -path \"./Makefile\" | xargs rm -rf" >>Makefile


file="$project_name.c"
touch $file
if [ "$?" != "0" ]
then
    exit 0
fi

echo "#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/unistd.h>
#include <linux/sched.h>
MODULE_LICENSE(\"Dual BSD/GPL\");

#define _DEBUG
#ifdef _DEBUG
#define kprintk(fmt,args...) printk(KERN_DEBUG fmt,##args)
#define kprintf(fmt,args...) printf(fmt,##args)
#define kperror(str) perror(str)
#else
#define kprintk
#define kprintf
#define kperror
#endif


int ${project_name}_init(void)
{

    kprintk(\"$project_name init\\\n\");
    return 0;
}

void ${project_name}_exit(void)
{
    kprintk(\"$project_name exit\\\\n\");
}


module_init(${project_name}_init);
module_exit(${project_name}_exit);" >> $file

echo "ok!success!"
