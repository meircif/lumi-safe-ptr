CXX?=g++
CXXA=$(CXX) -Iinclude -fsyntax-only

.PHONY: test-success 

test-success:
	$(CXXA) tests/test.cpp

test-missing-check:
	! $(CXXA) -DMAKE_MISSING_CHECK  tests/test.cpp

test-cycle-error:
	! $(CXXA) -DMAKE_CYCLE_ERROR tests/test.cpp
