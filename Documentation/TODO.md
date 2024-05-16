# TODO Tasks

Need to compile latest Github Repo hackRF Libraries from Source
    -> Much more up to date than the apt version

How to install hackrf dev libraries from source? 

cd hackrf/host
mkdir build
cd build
cmake ..
make
sudo make install
sudo ldconfig

* Possibly need to perform a firmware update. 

Setup Github

GOAL 1: Run hackrf-utils and report board info. DONE
GOAL 2: Tune Hack RF Receive Settings and report current configuration
GOAL 3: Access IQ Data and perform some basic pre-processing. 


## Work Needed for GOAL 2

### Referencing hackrf_sweep.c

Notes on how an example program works with hackrf_sweep
    * Configures and pre_loads fftw in lines 688:697

Start of HackRF setup is at line 713

* Initialize Hackrf driver
* Open Hackrf by serial number
    * What is needed to get the serial number, and does the hackrf_open_by_serial have a fall back to open the first on the dev list? 
* fft file output open
* setvbuf to have a bigger output buffer. 
* setup signal catcher callback handler
* call hackrf_sample_rate_set
    * sets sample rate to DEFAULT_SAMPLE_RATE_HZ
* call baseband filter bandwidth set (For Hardware handling of baseband filter?)
* hackrf_set_vga_gain
* hackrf_set_lna_gain
* (For sweep specifically, configure a set whole number of sweep steps to sweep across the whole configured bandwidth)
* setup ifft output once to make sure it's ready and configured, when the real call back data starts flowing. 


## First "Hello World" Version will be an FM Receiver

Immediately in main: 

Initialize:

* demod
* dongle
* output
* controller

In initializers: 

### Dongle Init: 

The dongle_state contains: 

Primitive Types: 

	int      exit_flag;
    int      dev_index;
	uint32_t freq;
	uint32_t rate;
	int      gain;
	uint16_t buf16[MAXIMUM_BUF_LENGTH];
	uint32_t buf_len;
	int      ppm_error;
	int      offset_tuning;
	int      direct_sampling;
	int      mute;

with `buf16` being the raw samples from the SDR device. The size of which will depend on the hardware device targetted.  

Dongle also contains: 

	pthread_t thread;
	rtlsdr_dev_t *dev;
	struct demod_state *demod_target;

With rtlsdr_dev_t being the pointer to the hardware device being targeted. This will need to be variable for our application, to be able to target rttsdr or hackrf. 


Pass in a pointer to the dongle_state\
Modify the dongle fields.\ 
dongle_state data structure has a reference to the demod:\
    `dongle_state->&demod;`

### Demod Init: 
There are a number of trivial types: 

    int      exit_flag;
    int16_t  lowpassed[MAXIMUM_BUF_LENGTH];
    int      lp_len;
    int16_t  lp_i_hist[10][6];
    int16_t  lp_q_hist[10][6];
    int16_t  result[MAXIMUM_BUF_LENGTH];
    int16_t  droop_i_hist[9];
    int16_t  droop_q_hist[9];
    int      result_len;
    int      rate_in;
    int      rate_out;
    int      rate_out2;
    int      now_r, now_j;
    int      pre_r, pre_j;
    int      prev_index;
    int      downsample;    /* min 1, max 256 */
    int      post_downsample;
    int      output_scale;
    int      squelch_level, conseq_squelch, squelch_hits, terminate_on_squelch;
    int      downsample_passes;
    int      comp_fir_size;
    int      custom_atan;
    int      deemph, deemph_a;
    int      now_lpr;
    int      prev_lpr_index;
    int      dc_block, dc_avg;

Then there are some pointers: 

    pthread_t thread;
    void (*mode_demod)(struct demod_state*);
    pthread_rwlock_t rw;
    pthread_cond_t ready;
    pthread_mutex_t ready_m;


The function pointer `(*mode_demod)(struct demod_state*)` gets initialized to the default function `void fm_demod(struct demod_state *s)` in demod_init. Any call of demod_state d->mode_demod(d) will pass this state into the fm_demod structure. 

The pthread variables should be replaced with modern c++ concurrency tools. 

### Output Init

Output state is fairly simple: 

Output state contains a;
* file pointer
* filename
* an array for storing `result` which is likely the result from demod
* sample rate


# GO BACK TO DONGLE_STATE TO UNDERSTAND FIELDS


Setup multiple threads. 


* Controller Thread
    * Responsible for: 
        * Setting the sampling rate
        * Setting the tuned frequency

* Output Thread
    * Responsible for writing to "output_state" pointer. 
    * This writes to a desired output file (or stdout if none is provided.)



# Design/Development

The following Flow diagram outlines the general structure to getting data from an SDR (This specifically is rtlSDR) This diagram should be agnostic to specific device used. 

![Generic SDR Control Logic](/home/fullofbologna/dev_env/CppDev/HackRF_Dev/FlowDiagram.png)


Dongle
    Base Dongle Class
        HackRF Child Class
        RTLSDR Child Class

Demod
    Base Demod Class
        FM Child Class
        FSK Child Class
        AM Child Class
        USB Child Class
        LSB Child Class
        BPSK Child Class
        Specialized Demodulation
            TACAN
            GPS
            FLEX/POCSAG

Output
    Base Output Class
        File Write
        FFT Write
        FFT Display
        

Manager
    Initializes Above Objects
    Connect Signals
    Set Dongle Settings
    Set Demod Settings
    Create Threads





