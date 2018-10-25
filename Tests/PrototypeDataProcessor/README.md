## Dependencies


### Python

    ```
    sudo apt install python3-pip
    python -mpip install -U pip
    python -mpip install -U matplotlib
    sudo apt-get install python3-matplotlib
    ```

### Octave

To install and setup octave, use the follow commands:

    ```
    # add repository
    sudo add-apt-repository ppa:octave/stable
    sudo apt-get update
    # install Octave
    sudo apt-get install octave
    sudo apt-get install liboctave-dev
    # other packages dependencies
    sudo apt-get install matplotlib
    sudo apt-get install gnuplot
    sudo apt-get install epstool
    sudo apt-get install transfig
    sudo apt-get install pstoedit
    ```

Install statistic packeges on Octave to run the simulations. Run the follow command to start Octave CLI:

    ```
    octave-cli
    ```

Inside Octave CLI, run the folloe commands:

    ```
    octave> pkg -forge install io
    octave> pkg -forge install statistics
    ```

After running these commands, a directory on home called .config/octave will appear. But it may have some ownership/access problems. To solve it, run this command on Shell terminal:

    ```
    sudo chown $USER ~/.config/octave/qt-settings
    ```

---

## Structure

This set of scripts perform a set of simulations  over actual pcap inter-packet times to fit stochatic models, and avaluate  wich perform the best fitting, and compare with AIC and BIC. Details on run, use `--help` as scripts arguments for details on the run.

---

- __pcap-filter.sh__ : extract inter packet times from pcaps
    + _timerelative2timedelta.m_: script used by pcap filter


---

- __dataProcessor.m__: run simulations and stores the data on data/ directory
    + _adiff.m_: calc the absolute difference 
    + _cdfCauchyPlot.m_: create the values of a Cauchy CDF  distribution, and plot in a figure
    + _cdfExponentialPlot.m_: create the values of a Exponential CDF  distribution, and plot in a figure
    + _cdfNormalPlot.m_: create the values of a Normal CDF  distribution, and plot in a figure
    + _cdfWeibullPlot.m_: create the values of a Weibull CDF  distribution, and plot in a figure
    + _cdfParetoPlot.m_: create the values of a Pareto CDF  distribution, and plot in a figure
    + _cdfplot.m_: create the values of a Cauchy CDF  distribution, and plot in a figure
    + _computeCost.m_: compute cost for linear regression
    + _cumulativeData.m_: acumulates a vector
    + _gradientDescent.m_: gradient descendent algorithm
    + _informationCriterion.m_:
    + _likehood\_log.m_:
    + _matrix2File.m_: save matrix into a text file
    + _empiricalCdf.m_: eval empirical CDF
    + _plotData.m_: wrapper for plot x and y data
    + _qqPlot.m_: wrapper for qqplots on octave wraper
    + _setxlabels.m_: set x tick labels on axis on figures
    + _sff2File.m_: vector to file
    + __data/__: place where dataProcessor.m saves the generated data
    + __figures/__: figures plotted by dataProcessor

---

- __calcCostFunction.py__: aux script, this script calcs the cost function for the simulated data and saves in the file costFunction.dat.

---

- __Not used files__:
    - _2matrix2File.m_
    - _calcCostFunction2.py_: test version of calcCostFunction.py
    - _empiricalCdf2.m_ 
    - _featureNormalize.m_
    - _load_testData.m_
    - _modelFittingEvaluation-plots.sh_: old plot script
    - _vector2File.m_: sames as sff2File
    - _xlabels.m_: 
    - _run.sh_: old run, does not work
    - _cdfPoissonPlot.m_: create the values of a Poisson CDF  distribution, and plot in a figure
    - _plotCostFunction.sh_: 









