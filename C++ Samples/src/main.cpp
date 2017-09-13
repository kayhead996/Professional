#include "assign3.h"


/*
 * Main takes args as specified in document
 */
int main(int argc, char *argv[]) {
    string **arg_list = process_args(argc, argv);
    run_sim(arg_list);
    return 0;
}


/*
 * Processes the arg list and TERMINATES if args are incorrect
 */
string **process_args(int argc, char *argv[]) {
    string **argv_ret = new string*[argc];
    ifstream myfile;
    string fname;

    if (argc > 8) {
        for (int i = 0; i < argc; i++)
            argv_ret[i] = new string(argv[i]); 
        
        if (FILE_ARG.compare(*(argv_ret[FILE_IND])) != 0) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }

        fname = *(argv_ret[FILE_NAME_IND]);
        myfile.open(fname);

        if (!myfile.good()) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }
        myfile.close();

        if (DIR_ARG.compare(*(argv_ret[DIR_IND])) != 0) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }

        fname = *(argv_ret[DIR_NAME_IND]);
        myfile.open(fname);
        if (!myfile.good()) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }
        myfile.close();

        if (DISK_ARG.compare(*(argv_ret[DISK_IND])) != 0) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }

        if (BLK_ARG.compare(*(argv_ret[BLK_IND])) != 0) {
            cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;
            exit(EXIT_FAILURE);
        }

        cout << "Args processed sucessfully" << endl;
        return argv_ret;
    }

    cout << "Usage: ./FSSimulator -f <file_list> -d <dir_list> -s <disk_size> -b <block_size>" << endl;

    exit(EXIT_FAILURE);
}
