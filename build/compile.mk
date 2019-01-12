OBJ_DIR = obj
LIB_DIR = lib

# Objects Files
SOURCES := $(wildcard src/*.cpp) $(wildcard src/*.c)
OBJECTS = $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SOURCES))))
DEPS = $(OBJECTS:%.o=%.d)

$(TARGET) : $(OBJECTS)
	@if [ ! -d $(LIB_DIR) ]; then mkdir -p $(LIB_DIR); fi;\
	$(AR) cq $(LIB_DIR)/$(TARGET) $(OBJECTS)
	
$(OBJ_DIR)/%.o : %.cpp
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
	echo "    "Compiling \[ $< \]...; \
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)

$(OBJ_DIR)/%.o : %.c
	@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
	echo "    "Compiling \[ $< \]...; \
	$(CXX) $(CFLAGS) -c $< -o $@ $(INCLUDE_DIRS)
	
define DEP_BUILD
@if [ ! -d $(OBJ_DIR) ]; then mkdir -p $(OBJ_DIR); fi;\
set -e; rm -f $@; \
$(CXX) -MM $(CFLAGS) $< $(INCLUDE_DIRS) > $@.$$$$; \
sed 's,\($*\)\.o[ :]*,$(OBJ_DIR)/\1.o $@ : ,g' < $@.$$$$ > $@; \
rm -f $@.$$$$
endef

$(OBJ_DIR)/%.d : %.cpp
	$(DEP_BUILD)
$(OBJ_DIR)/%.d: %.c
	$(DEP_BUILD)

-include $(DEPS)
.PHONY : clean
clean :
	rm -rf $(LIB_DIR) $(OBJ_DIR) 

