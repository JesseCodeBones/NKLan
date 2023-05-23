import os, subprocess
class LangRunner:
  def __init__(self) -> None:
    pass
  def runTests(self) -> None:
    testsDir = f'{os.getcwd()}/test/lang-test'
    binPath = f'{os.getcwd()}/build/nklang'
    files = os.listdir(testsDir)
    for file in files:
      target = f'{testsDir}/{file}'
      result = subprocess.run([binPath, target], stdout=subprocess.PIPE)
      if result.returncode != 0:
        print(result.stderr.decode('utf-8'))
        raise RuntimeError(f'return code not zero={result.returncode}')
      else:
        print(result.stdout.decode('utf-8'))
if __name__ == '__main__':
  mLangRunner = LangRunner()
  mLangRunner.runTests()

