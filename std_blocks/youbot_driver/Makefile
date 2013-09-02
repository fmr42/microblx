# Configure this:
SOEM_DIR=/home/mk/src/git/SOEM1.2.5
# 1.3: SOEM_LIBS=$(SOEM_DIR)/lib/linux/libsoem.a $(SOEM_DIR)/lib/linux/liboshw.a $(SOEM_DIR)/lib/linux/libosal.a
# 1.3: SOEM_INC=-I$(SOEM_DIR)/soem/ -I$(SOEM_DIR)/osal/ -I$(SOEM_DIR)/oshw/linux/
SOEM_LIBS=$(SOEM_DIR)/src/libsoem.a
SOEM_INC=-I$(SOEM_DIR)/src/


ROOT_DIR=$(CURDIR)/../..
include $(ROOT_DIR)/make.conf
UBX_DIR=$(ROOT_DIR)/src/



TYPES:=$(wildcard types/*.h)
HEXARRS:=$(TYPES:%=%.hexarr)

youbot_driver.so: youbot_driver.o $(UBX_DIR)/libubx.so 
	${CC} $(CFLAGS_SHARED) -o youbot_driver.so youbot_driver.o $(SOEM_LIBS) $(UBX_DIR)/libubx.so -pthread -lrt

youbot_driver.o: youbot_driver.c youbot_driver.h $(UBX_DIR)/ubx.h $(UBX_DIR)/ubx_types.h $(UBX_DIR)/ubx.c $(HEXARRS)
	${CC} -fPIC -pthread -I$(UBX_DIR) $(SOEM_INC) -c $(CFLAGS) youbot_driver.c

clean:
	rm -f *.o *.so *~ core $(HEXARRS)