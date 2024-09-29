import getopt
import sys
import initialize

if __name__ == "__main__":
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'i:p::c:', ['ip', 'port', 'count'])
        # print(opts)
        # print(args)
        initialize.initialize_program(opts)
    except getopt.GetoptError:
        print("Arguments are missing or wrong")


