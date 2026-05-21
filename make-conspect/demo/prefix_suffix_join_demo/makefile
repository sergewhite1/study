SUBFILE_NAMES = Problem1 Problem2
S1 = String_1 AAA
S2 = String_2 BBB
prefix_demo = $(addprefix p_, $(SUBFILE_NAMES))
suffix_demo = $(addsuffix s_, $(SUBFILE_NAMES))
join_demo = $(join $(S1), $(S2))

.PHONY: print-deps
print-deps:
	@echo Hello!
	@echo prefix_demo = $(prefix_demo)
	@echo suffix_demo = $(suffix_demo)
	@echo join_demo   = $(join_demo)

