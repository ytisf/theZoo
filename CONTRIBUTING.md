# Contributing to theZoo

First off, thank you for taking the time to contribute to `theZoo`.

The following is a set of guidelines as how to contribute, be it by Pull requests or by opening tickets and raising issues. Use your best judgment and feel free to propose changes to this document as well.

## Contribution
### Reporting Bugs
Before creating bug reports please check the `bugs` section on GitHub. It might already be there... When you are creating a bug report, please include as many details as possible. General bug openings with 'this does not work' are probably just going to be closed as they are impossible to triage.

Explain the problem and include additional details to help maintainers reproduce the problem:

* Use a clear and descriptive title for the issue to identify the problem.
* Describe the exact steps which reproduce the problem in as many details as possible.
* Include system information (Python version, OS version, etc.).
* Explain which behaviour you expected to see instead and why.

**DO NOT** open bugs for malware not executing unless you are confident that the file itself is broken. Some malware won't run in virtualisation, some have anti debugging and some are DLLs. We can always recommend more information on the topic such as [this wonderful book](https://www.amazon.com/Practical-Malware-Analysis-Hands-Dissecting). But `theZoo`'s bug tracking system is not a support channel.   

### Requesting Samples
If a particular sample is of interest to you and it cannot be find the `theZoo` kindly [send an email to](mailto:thezoo+codeofconduct@morirt.com). Please do **not** open up an bug/feature request for a sample. We will attempt to upload that sample in the next batch.

### Database Contributions
Please see `prep_file.py` to assist you in creating the directory you need. However, this will not fill out the database. You can use any of the SQLite3 editors out there to add it to the database [`conf/maldb.db`]. Make sure you are accurate about your description, tags and info. The reliability and accuracy of the database is the main purpose for the existence of `theZoo`. Without a credible database this is just another malware dump.

Edit the database and remember that file paths are case sensitive.  

### Suggesting Enhancements
Similar to **Reporting Bugs** section. Please be descriptive. What exactly it is that you would like and what is the workflow you are seeing. The more descriptive you are the more likely it is for others in the community to vote for this and we will know to prioritise it.
