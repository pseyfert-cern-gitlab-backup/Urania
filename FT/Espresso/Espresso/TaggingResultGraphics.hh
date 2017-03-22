/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Tagger performance and calibration utilities
 * @details This header file declares several functions
 * that create ROOT graphics objects from Espresso objects.
 */

#ifndef ESPRESSO_TAGGINGRESULTGRAPHICS_HH 
#define ESPRESSO_TAGGINGRESULTGRAPHCIS_HH 1

#include <TGraph.h>
#include <TH1F.h>

#include "TaggingResult.hh"

namespace Espresso {

  /**
   * @brief Creates a TGraph of a binned tagging result.
   * @details Can be plotted AP for a standard plot.
   * Setting a fill color and plotting APE3 creates a banded region (e.g.
   * for kernel smoothed bin table).
   * @param[in] table BinTable to be plotted
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] sigmaConf sigma value to use for error bars
   */
  std::shared_ptr<TGraph> graphBinTable(const TaggingResult::BinTable& table, std::string, std::string title, int sigmaConf = 0);

  /**
   * @brief Creates a TGraph of the signal asymmetry vs decay time.
   * @details Can be plotted AP for a standard plot.
   * Setting a fill color and plotting APE3 creates a banded region (e.g.
   * for kernel smoothed bin table).
   * @param[in] table BinTable to be plotted
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] sigmaConf sigma value to use for error bars
   */
  std::shared_ptr<TGraph> graphTauTable(const TaggingResult::TauTable& table, std::string name, std::string title, int sigmaConf = 0);

  /**
   * @brief Creates a TGraph of a calibration function &omega;(&eta;).
   * @details Can be plotted AP for a standard plot.
   * Setting a fill color and plotting APE3 creates a banded region.
   * @param[in] cal Calibration object to be plotted
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] min minimum eta value
   * @param[in] max maximum eta value
   * @param[in] sigmaConf sigma value to use for error bars
   * @param[in] npx Number of interpolated points; 1000 by default
   */
  std::shared_ptr<TGraph> graphCalibration(const Calibration& cal, std::string, std::string title, double min, double max,
					   int sigmaConf = 0, int npx = 1000);

  
  /**
   * @brief Prints a TGraph to a PNG file using the "P" plot style.
   * @param[in] graph TGraph to be printed
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void printGraph(std::shared_ptr<TGraph> graph, bool saveToRoot=false);

  /**
   * @brief Prints a TH1F to a PNG file using the "E" plot style.
   * @param[in] hist TH1F to be printed
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void printHistogram(std::shared_ptr<TH1F>, bool saveToRoot=false);
  
  /**
   * @brief Prints a TGraph to a PNG file using the "L" plot style.
   * @param[in] graph TGraph to be printed
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void printCurve(std::shared_ptr<TGraph>, bool saveToRoot=false);
  
  /**
   * @brief Prints a kernel smoothed graph of &omega; vs &eta;,
   * with shaded bands at 1 and 2 sigma in dark and light blue.
   * @param[in] table to be printed
   * @param[in] name Filename to be saved to
   * @param[in] title Title of the plot
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void printSmoothedBinTable(const TaggingResult::BinTable& table, std::string, std::string title, bool saveToRoot=false);

  /**
   * @brief Prints a kernel smoothed graph of &omega; vs &eta;,
   * with shaded bands at 1 and 2 sigma in dark and light blue.
   * @param[in] table to be printed
   * @param[in] name Filename to be saved to
   * @param[in] title Title of the plot
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void printSmoothedTauTable(const TaggingResult::TauTable& table, std::string, std::string title, bool saveToRoot=false);

  /**
   * @brief Prints a plot of the calibration over data points of &omega; vs &eta;.
   * @details Includes shaded bands representing the calibration uncertainty at 1 and 2 sigma in green and yellow
   * @param[in] cal Calibration object
   * @param[in] table Table of data points
   * @param[in] name Filename to be saved to
   * @param[in] title Title of the plot
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void overlayDataAndCalibration(const Calibration& cal, const TaggingResult::BinTable& table,
                                 std::string name, std::string title, double min, double max, bool saveToRoot=false);
  

  /**
   * @brief Prints a plot of the calibration over kernel smoothed &omega; vs &eta; data.
   * @detials Includes shaded bands representing the calibration uncertainty at 1 and 2 sigma in green and yellow
   * and dark and light blue shaded bands for the uncertainty in the data.
   * @param[in] cal Calibration object
   * @param[in] table Table of data points
   * @param[in] name Filename to be saved to
   * @param[in] title Title of the plot
   * @param[in] saveToRoot Whether to write TCanvas to current ROOT file
   */
  void overlaySmoothedDataAndCalibration(const Calibration& cal, const TaggingResult::BinTable& table,
                                         std::string name, std::string title, double min, double max, bool safeToRoot=false);
  

  /**
   * @brief Creates a TGraph of the ``integrated tagging power'' of a tagger.
   * @details This is the tagging power &epsilon;<sub>eff</sub>(&omega;<sub>0</sub>)
   * for all tags with &omega; < &omega;<sub>0</sub>.
   * Can be plotted with AL option for a curve (via printCurve).
   * @param[in] tag TaggingResult object
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] npx Number of interpolated points; 1000 by default
   */
  std::shared_ptr<TGraph> graphIntegratedTaggingPower(const TaggingResult& tag, std::string, std::string title, int npx = 1000);

  /**
   * @brief Creates a TGraph of the receiver operating characteristic curve of a tagger.
   * @details Can be plotted with AL option for a curve (via printCurve).
   * @param[in] tag TaggingResult object
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] npx Number of interpolated points; 1000 by default
   */
  std::shared_ptr<TGraph> graphROC(const TaggingResult& tag, std::string, std::string title, int npx = 1000);

  /**
   * @brief Creates a histogram of the tagger's calibrated eta distribution.
   * @param[in] tag TaggingResult object
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] min Lower bound of histogram
   * @param[in] max Upper bound of histogram
   */
  std::shared_ptr<TH1F> graphEtaDist(const TaggingResult& tag, std::string, std::string title, int bins = 100, double min = 0, double max = 0.5);

  /**
   * @brief Creates a histogram of the tagger's calibrated eta distribution,
   * only for correctly tagged events.
   * @param[in] tag TaggingResult object
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] min Lower bound of histogram
   * @param[in] max Upper bound of histogram
   */
  std::shared_ptr<TH1F> graphEtaDistRight(const TaggingResult& tag, std::string, std::string title, int bins = 100, double min = 0, double max = 0.5);

  /**
   * @brief Creates a histogram of the tagger's calibrated eta distribution,
   * only for incorrectly tagged events.
   * @param[in] tag TaggingResult object
   * @param[in] name a string used to create the ROOT object's name
   * @param[in] title a string used to create the ROOT object's title
   * @param[in] min Lower bound of histogram
   * @param[in] max Upper bound of histogram
   */
  std::shared_ptr<TH1F> graphEtaDistWrong(const TaggingResult& tag, std::string, std::string title, int bins = 100, double min = 0, double max = 0.5);

}


#endif // ESPRESSO_TAGGINGRESULTGRAPHICS_HH

/**
 * @}
 */
